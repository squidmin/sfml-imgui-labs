#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <vector>
#include <iostream>
#include <numeric>

class BalancedSumsAnimation {
public:

    BalancedSumsAnimation(const std::vector<int>& arr) : arr(arr), leftSum(0), rightSum(0), currentIndex(0) {
        // Calculate total sum
        for (auto& num : arr) {
            rightSum += num;
        }
    }

    bool update(float deltaTime) {
        if (currentIndex < arr.size()) {
            if (currentIndex > 0) {
                leftSum += arr[currentIndex - 1];
            }

            if (leftSum == rightSum) {
                balanceIndex = currentIndex;  // Found balance point
            }

            rightSum -= arr[currentIndex];
            currentIndex++;
            return false;  // Continue processing
        }
        return true;  // Finished processing
    }

    // Add a new method to control the update direction
    void manualUpdate(bool forward) {
        if (forward) {
        if (currentIndex < arr.size()) {
            if (currentIndex > 0) {
                leftSum += arr[currentIndex - 1];
            }
            rightSum -= arr[currentIndex];
            if (leftSum == rightSum) {
                balanceIndex = currentIndex;
            }
            currentIndex++;
        }
    } else {
        if (currentIndex > 0) {
            currentIndex--;
            leftSum = std::accumulate(arr.begin(), arr.begin() + currentIndex, 0);
            rightSum = std::accumulate(arr.begin() + currentIndex, arr.end(), 0);
            if (leftSum == rightSum) {
                balanceIndex = currentIndex;
            }
        } else {
            resetAnimation();
        }
    }
    }

    void draw() {
        // Set a default size for the window that is wider and allow the window to be resized
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x * 0.9f, ImGui::GetIO().DisplaySize.y * 0.6f), ImGuiCond_FirstUseEver);
    
        ImGui::Begin("Balanced Sums Animation");  // Removed the AlwaysAutoResize flag to allow resizing


        // Add a Play button and a speed control slider
        if (ImGui::Button(isPlaying ? "Pause" : "Play")) {
            isPlaying = !isPlaying;  // Toggle the playing state
        }
        ImGui::SameLine();
        ImGui::SliderFloat("Speed", &playSpeed, 0.1f, 5.0f, "Speed: %.1f"); // Slider to control the speed

        // Adjust the "Previous" button width to ensure the text fits
        float buttonWidth = ImGui::CalcTextSize("Previous").x + ImGui::GetStyle().FramePadding.x * 2.0f;
        if (ImGui::Button("Previous", ImVec2(buttonWidth, 0))) {
            manualUpdate(false);  // Move one step back in the animation
            isPlaying = false;  // Stop playing when manually stepping back
        }
        ImGui::SameLine();
        // Ensure the "Next" button is the same width as the "Previous" button for consistency
        if (ImGui::Button("Next", ImVec2(buttonWidth, 0))) {
            manualUpdate(true);  // Move one step forward in the animation
            isPlaying = false;  // Stop playing when manually stepping forward
        }
        ImGui::SameLine();
        if (ImGui::Button("Reset")) {
            resetAnimation();  // Reset the animation state when clicked
        }

        ImGui::Spacing();
        
        // Total sum progress bar
        int totalSum = leftSum + rightSum;  // Calculate the total sum for display
        ImGui::Text("Total Sum: %d", rightSum);  // Draw the right sum part of the total sum progress bar in red
        ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.86f, 0.2f, 0.2f, 1.0f)); // Red color
        ImGui::ProgressBar((float)rightSum / rightSum, ImVec2(-1, 0), "");
        ImGui::PopStyleColor();

        // Overlay the left sum part of the total sum progress bar in blue
        ImGui::SameLine(0.0f, 0.0f);  // Overlay on the same line
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() - ImGui::GetItemRectSize().x); // Move cursor back to the start of the progress bar
        ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.2f, 0.6f, 0.86f, 1.0f)); // Blue color
        ImGui::ProgressBar((float)leftSum / totalSum, ImVec2(-1, 0), "");
        ImGui::PopStyleColor();

        // Iterate over the array to display it with progress bars
        for (int i = 0; i < arr.size(); ++i) {
            // If this is the current index, draw an arrow with the index to indicate the left pointer's position
            if (i == currentIndex) {
                ImGui::Text("[%d]->", i);  // Index and arrow symbol
                ImGui::SameLine();
            } else {
                ImGui::Text("    ");  // Spaces to align with other rows (adjust as needed)
                ImGui::SameLine();
            }

            // Text color for values accumulated into the leftSum
            if (i == balanceIndex) {
                ImGui::TextColored(ImVec4(0, 1, 0, 1), "%d", arr[i]);
            } else if (i < currentIndex) {
                ImGui::TextColored(ImVec4(0.75f, 0.75f, 0.75f, 1.0f), "%d", arr[i]);  // Light gray color
            } else {
                ImGui::Text("%d", arr[i]);
            }

            // Calculate the space for the progress bars so they are symmetrical
            float progressBarWidth = (ImGui::GetWindowWidth() - 100 - ImGui::CalcTextSize("0").x * 2.0f) / 2.0f;
            ImGui::SameLine(100);

            // Left progress bar in blue
            ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.2f, 0.6f, 0.86f, 1.0f)); // Blue color
            float leftBarValue = (i < currentIndex) ? (float)arr[i] / totalSum : 0.0f;
            ImGui::ProgressBar(leftBarValue, ImVec2(progressBarWidth, 0), "");
            ImGui::PopStyleColor();
            
            // Right progress bar in red
            ImGui::SameLine(ImGui::GetWindowWidth() - progressBarWidth - ImGui::CalcTextSize("0").x * 2.0f);
            ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.86f, 0.2f, 0.2f, 1.0f)); // Red color
            float rightBarValue = (i >= currentIndex) ? (float)arr[i] / totalSum : 0.0f;
            ImGui::ProgressBar(rightBarValue, ImVec2(progressBarWidth, 0), "");
            ImGui::PopStyleColor();
        }

        // Display the sums and balance found message
        ImGui::Text("Left Sum: %d", leftSum);
        ImGui::SameLine();
        ImGui::Text("Right Sum: %d", rightSum);

        if (balanceIndex != -1) {
            ImGui::TextColored(ImVec4(0, 1, 0, 1), "Balance found at index %d", balanceIndex);
        }

        ImGui::End();  // End of ImGui window
    }

    const std::vector<int>& getArr() const {
      return arr;
    }

    const int getLeftSum() {
        return this->leftSum;
    }

    const int getRightSum() {
        return this->rightSum;
    }

    const int getCurrentIndex() {
        return this->currentIndex;
    }

    void setCurrentIndex(int index) {
        currentIndex = index;
    }

    const bool getIsPlaying() {
        return this->isPlaying;
    }

    const float getPlaySpeed() {
        return this->playSpeed;
    }

    void resetAnimation() {
        currentIndex = 0;
        leftSum = 0;
        rightSum = std::accumulate(arr.begin(), arr.end(), 0);
        balanceIndex = -1;  // Reset balance index when animation is reset
        isPlaying = false;  // Stop the animation
    }


private:
    std::vector<int> arr;
    int leftSum;
    int rightSum;
    int currentIndex = 0;
    int balanceIndex = -1;  // Initialized to -1 to indicate no balance found initially
    bool isPlaying = false;  // To control the playback state
    float playSpeed = 1.0f;  // To control the speed of the animation
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 700), "Balanced Sums Animation");
    ImGui::SFML::Init(window);

    std::vector<int> arr = {4, 1, 7, 3, 5, 6, 2, 3, 1, 4, 5, 2, 8, 7, 10, 3, 2, 1, 4, 6};
    BalancedSumsAnimation animation(arr);

    sf::Clock playClock;  // Separate clock for handling play speed
    sf::Clock deltaClock;
    sf::Clock animationClock;  // Clock to manage animation updates
    float updateInterval = 500;  // Set the desired interval in milliseconds

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());
        
        if (animation.getIsPlaying() && animationClock.getElapsedTime().asMilliseconds() >= (updateInterval / animation.getPlaySpeed())) {
            if (animation.getCurrentIndex() >= animation.getArr().size()) {
                animation.resetAnimation();  // Reset animation state if it's at the end
            } else {
                animation.manualUpdate(true);  // Otherwise, continue playing the animation
            }
            animationClock.restart();
        }

        animation.draw();

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}
