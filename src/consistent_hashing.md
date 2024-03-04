# Consistent hashing

## Overview

The Consistent Hashing Simulation is a visualization tool developed using SFML and ImGui libraries in C++. It demonstrates the concept of consistent hashing, a key technique used in distributed systems to achieve even distribution of data across a cluster of nodes with minimal redistribution when nodes are added or removed.

## Features

- **Dynamic Hash Ring Visualization**: Displays a hash ring where both nodes and keys are mapped based on their hash values.
- **Interactive Node and Key Management**: Allows users to add or remove nodes and keys dynamically to observe how the system adapts.
- **Animation Control**: Users can pause, play, or reset the animation to study the system's behavior at their own pace.

## Dependencies

- **SFML**: Used for rendering the graphical interface.
- **ImGui + ImGui-SFML**: Provides an immediate mode graphical user interface to interact with the simulation.
- **C++ Standard Libraries**: Utilizes standard libraries for data structures and utilities.

## Implementation Details

### Main Components

- **Hash Ring**: The central concept, represented as a circle where nodes and keys are placed based on their hash values.
- **Nodes and Keys**: Entities that can be added to or removed from the hash ring. Each node can "own" multiple keys based on the hash value proximity.

### Key Functions

- **`calculateHash`**: Calculates the hash value of a string (representing either a node ID or a key ID) modulo the maximum hash ring size to ensure it falls within the ring.
  
- **`findResponsibleNodeHash`**: Determines which node is responsible for a given key based on the closest node hash value that is greater than or equal to the key's hash value.

- **`drawHashRing`**: Renders the visual representation of the hash ring.

- **`drawNodes`**: Draws nodes on the hash ring, distributed according to their hash values.

- **`drawText`**: Displays textual information such as node and key IDs on the interface.

### Struct `HashRing`

- Manages the nodes and keys within the hash ring.
- Provides methods to add/remove nodes and keys.
- Calculates positions of nodes/keys for rendering.

## Usage

1. **Starting the Simulation**: Run the executable to launch the simulation window.
2. **Interacting with the GUI**: Use the provided ImGui interface to add nodes and keys, control animation, and reset the state as needed.
3. **Observing Changes**: Watch how the hash ring adapts when nodes and keys are added or removed, showcasing the principles of consistent hashing.

## Compilation

```bash
cd cmake-build-debug
cmake -DCMAKE_CXX_COMPILER=/usr/bin/c++ ..
cmake --build .
```

## Conclusion

The Consistent Hashing Simulation provides a hands-on way to understand the dynamics of consistent hashing in distributed systems. Through interactive visualization, users can gain insights into data distribution, load balancing, and the efficient management of nodes and keys within a hash ring.
