#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <string>
#include <map>

enum class AnimationState {
    Paused,
    Playing,
    Reset
};

const unsigned int HASH_RING_MAX = 360;

unsigned int findResponsibleNodeHash(const std::map<unsigned int, std::string>& ring, unsigned int keyHash) {
    auto it = ring.upper_bound(keyHash); // Find the next node in the ring
    if (it != ring.end()) {
        return it->first; // If found, return the next node's hash
    }
    // If not found (meaning we're at the end of the ring), wrap around to the first node
    return ring.begin()->first;
}

unsigned int calculateHash(const std::string& str) {
    std::hash<std::string> hasher;
    auto hashed = hasher(str);
    return hashed % HASH_RING_MAX; // Modulate by the hash ring size
}

// Draw a circle representing the hash ring
void drawHashRing(sf::RenderWindow& window, const sf::Vector2f& position, float radius) {
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(2.f);
    circle.setOutlineColor(sf::Color(100, 100, 250));
    circle.setPosition(position.x - radius, position.y - radius);
    window.draw(circle);
}

struct HashRing {
    std::map<unsigned int, std::string> ring; // Hash value to identifier (node or key)

    void addNode(const std::string& nodeId) {
        unsigned int hash = calculateHash(nodeId); // Use the renamed function
        ring[hash] = "Node: " + nodeId;
    }

    void removeNode(const std::string& nodeId) {
        unsigned int hash = calculateHash(nodeId); // Use the renamed function
        ring.erase(hash);
    }

    void addKey(const std::string& keyId) {
        unsigned int hash = calculateHash(keyId); // Use the renamed function
        ring[hash] = "Key: " + keyId;
    }

    void removeKey(const std::string& keyId) {
        unsigned int hash = calculateHash(keyId);
        ring.erase(hash);
    }

    // Calculate the positions of nodes and keys on the hash ring
    std::map<unsigned int, sf::Vector2f> calculatePositions(sf::RenderWindow& window, float radius) {
        std::map<unsigned int, sf::Vector2f> positions;

        sf::Vector2f center(window.getSize().x / 2.0f, window.getSize().y / 2.0f); // Calculate the center of the window

        // Iterate over the hash ring and calculate the position for each node and key
        for (const auto& [hash, label] : ring) {
            float angle = hash * (2 * M_PI / HASH_RING_MAX); // Convert the hash value to an angle (in radians)
            sf::Vector2f position(radius * cos(angle) + center.x, radius * sin(angle) + center.y); // Calculate the position using the angle and radius
            positions[hash] = position; // Insert the position into the map with the corresponding hash
        }

        return positions;
    }
};

// Draw text labels
void drawText(sf::RenderWindow& window, const std::string& text, sf::Vector2f position, sf::Color color, unsigned int size) {
    static sf::Font font;
    static bool fontLoaded = false;
    if (!fontLoaded) {
        if (!font.loadFromFile("../../fonts/Consolas.ttf")) {
            std::cerr << "Could not load font\n";
            return;
        }
        fontLoaded = true;
    }
    sf::Text sfText(text, font, size);
    sfText.setFillColor(color);
    sfText.setPosition(position);
    window.draw(sfText);
}

// Draw nodes on the hash ring
void drawNodes(sf::RenderWindow& window, const sf::Vector2f& center, float radius, int nodeCount) {
    float angleStep = 360.0f / nodeCount;
    for (int i = 0; i < nodeCount; ++i) {
        float angle = i * angleStep;
        sf::Vector2f pos = center + sf::Vector2f(radius * cos(angle * 3.14159265f / 180.0f), radius * sin(angle * 3.14159265f / 180.0f));

        sf::CircleShape node(5.f);
        node.setFillColor(sf::Color::Red);
        node.setPosition(pos);
        window.draw(node);
    }
}

int main() {
    srand(time(nullptr)); // Set a random seed based on current time

    sf::RenderWindow window(sf::VideoMode(1200, 600), "Consistent Hashing");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    char nodeInputBuffer[128] = "";
    char keyInputBuffer[128] = "";

    AnimationState animationState = AnimationState::Paused;
    HashRing hashRing;
    std::map<unsigned int, sf::Vector2f> positions;

    // Initialize a node and key
    hashRing.addNode("Node1");
    hashRing.addKey("Key1");

    ImGuiIO& io = ImGui::GetIO();
    ImFont* biggerFont = io.Fonts->AddFontDefault();
    if (biggerFont) {
        biggerFont->Scale = 1.2f;
    }
    ImGui::SFML::UpdateFontTexture(); // After adding fonts, rebuild the font atlas

    ImGui::StyleColorsDark(); 

    sf::Clock deltaClock;
    sf::Time timeSinceLastAddition = sf::Time::Zero;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Update the elapsed time since last addition
        sf::Time deltaTime = deltaClock.restart(); // Move restart() here to ensure it's called once per frame
        if (animationState == AnimationState::Playing) {
            timeSinceLastAddition += deltaTime;
        }

        ImGui::SFML::Update(window, deltaTime);

        ImGui::SetNextWindowSize(ImVec2(250, 500), ImGuiCond_FirstUseEver);

        ImGui::Begin("Control Panel");

        if (ImGui::Button("Play")) {
            animationState = AnimationState::Playing; // Just set the state to Playing
            timeSinceLastAddition = sf::Time::Zero; // Optionally reset the timer here
        }
        if (ImGui::Button("Pause")) {
            animationState = AnimationState::Paused;
        }
        if (ImGui::Button("Reset")) {
            animationState = AnimationState::Reset;
        }

        // Add a node
        if (ImGui::InputText("Add Node", nodeInputBuffer, IM_ARRAYSIZE(nodeInputBuffer), ImGuiInputTextFlags_EnterReturnsTrue)) {
            hashRing.addNode(std::string(nodeInputBuffer));
            memset(nodeInputBuffer, 0, sizeof(nodeInputBuffer)); // Clear buffer after adding
            positions = hashRing.calculatePositions(window, 250); // Recalculate positions after adding a node
        }

        // Remove a node
        if (ImGui::Button("Remove Node")) {
            hashRing.removeNode(std::string(nodeInputBuffer));
            memset(nodeInputBuffer, 0, sizeof(nodeInputBuffer)); // Clear buffer after removing
        }

        ImGui::Separator();

        // Add a key
        if (ImGui::InputText("Add Key", keyInputBuffer, IM_ARRAYSIZE(keyInputBuffer), ImGuiInputTextFlags_EnterReturnsTrue)) {
            hashRing.addKey(std::string(keyInputBuffer));
            memset(keyInputBuffer, 0, sizeof(keyInputBuffer)); // Clear buffer after adding
        }

        // Remove a key
        if (ImGui::Button("Remove Key")) {
            hashRing.removeKey(std::string(keyInputBuffer)); // Assuming removeKey is implemented
            memset(keyInputBuffer, 0, sizeof(keyInputBuffer)); // Clear buffer after removing
        }

        // Logic to handle the animation state
        if (animationState == AnimationState::Playing) {
            timeSinceLastAddition += deltaTime; // Accumulate the time since the last addition
            if (timeSinceLastAddition.asSeconds() >= 1.0f) { // Every 1 second
                // Add a new node or key with a unique identifier
                hashRing.addNode("Node" + std::to_string(rand()));
                hashRing.addKey("Key" + std::to_string(rand()));
                timeSinceLastAddition = sf::Time::Zero; // Reset the timer

                // Recalculate positions for the new elements
                positions = hashRing.calculatePositions(window, 250);
            }
        } else if (animationState == AnimationState::Reset) {
            // Reset logic
            hashRing.ring.clear();
            hashRing.addNode("Node1"); // Re-add initial node
            positions = hashRing.calculatePositions(window, 250);
            animationState = AnimationState::Paused; // Set state to Paused after resetting
        }

        ImGui::End();

        window.clear(sf::Color(45, 45, 45)); // Set background to dark gray
        
        // Draw the hash ring
        sf::CircleShape hashRingShape(250); // Radius 250 for visualization
        hashRingShape.setFillColor(sf::Color::Transparent);
        hashRingShape.setOutlineThickness(2);
        hashRingShape.setOutlineColor(sf::Color::Black);
        hashRingShape.setPosition(window.getSize().x / 2 - 250, window.getSize().y / 2 - 250); // Centered
        window.draw(hashRingShape);

        positions = hashRing.calculatePositions(window, 250);

        // Draw the lines connecting keys to nodes
        for (const auto& [hash, label] : hashRing.ring) {
            if (label.find("Key:") != std::string::npos) {
                unsigned int nodeHash = findResponsibleNodeHash(hashRing.ring, hash);
                
                // Debug: Print out the hash values and positions to verify correctness
                std::cout << "Key Hash: " << hash << " at position " << positions[hash].x << ", " << positions[hash].y << std::endl;
                std::cout << "Node Hash: " << nodeHash << " at position " << positions[nodeHash].x << ", " << positions[nodeHash].y << std::endl;

                sf::VertexArray line(sf::Lines, 2);
                line[0].position = positions[hash]; // Position of the key
                line[1].position = positions[nodeHash]; // Position of the node responsible for this key
                line[0].color = sf::Color::Yellow; // Visible color for the line start
                line[1].color = sf::Color::Yellow; // Visible color for the line end
                window.draw(line);
            }
        }

        // Finally draw nodes and keys on top of everything
        for (const auto& [hash, label] : hashRing.ring) {
            sf::CircleShape shape(5);
            shape.setFillColor(label.find("Node:") != std::string::npos ? sf::Color::Blue : sf::Color::Red);
            shape.setPosition(positions[hash] - sf::Vector2f(5, 5)); // Adjust the position to center the shape on the calculated point
            window.draw(shape);

            drawText(window, label, positions[hash] + sf::Vector2f(5, -5), sf::Color::White, 12);
        }

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}
