# R-Type

![alt text](https://i0.wp.com/limitedgamenews.com/wp-content/uploads/2019/02/r-type-dimensions-ex-strictly-limited-games-nintendo-switch-cover-limitedgamenews.com_.jpg?ssl=1 "R-Type")

Welcome to the R-Type project! This document will guide you through the setup process, explain key components of the project, and provide resources for further information.

## Getting Started

To begin using the R-Type project, follow these steps for setting up and running the client and server:

### Installation & Setup

**1. Clone the repository:**

  ```bash
  $ git clone git@github.com:EpitechPromo2027/B-CPP-500-LYN-5-1-rtype-cyprien.diederichs.git
  $ cd r-type/
  ```

**2. Build the project using CMake:**

  In order to compile the project, run the following commands:

  ```bash
  $ cmake -S . -B build
  ```

  This will create the necessary build files and compile the project.

**3. Running the Client & Server:**

  Once compiled, you can run the client and server using the following commands:

  - To run the server:

    ```bash
    $ ./r-type_server
    ```

  - To run the client:

    ```bash
    $ ./r-type_client
    ```

### ECS (Entity Component System)

Our game engine is built around an **ECS** architecture, which helps in organizing and managing the game’s entities, components, and systems. The **ECS** implementation is located in a dynamic library (`libengine.so`), which is _loaded dynamically_ at runtime.

For detailed information on how to use the **ECS** in your development, visit our [GitHub Wiki about ECS](https://github.com/EpitechPromo2027/B-CPP-500-LYN-5-1-rtype-cyprien.diederichs/wiki/R%E2%80%90Type-ECS).

## Network

R-Type uses **UDP (User Datagram Protocol)** for its network communication, which allows for fast and efficient data transmission, essential for real-time multiplayer gaming. The protocol is implemented in a **binary format** to minimize data size and improve performance.

For detailed information on the network implementation, refer to our [GitHub Wiki about Networking](https://github.com/EpitechPromo2027/B-CPP-500-LYN-5-1-rtype-cyprien.diederichs/wiki/Network)

### Cross-Platform Compatibility

Our network implementation is fully cross-platform compliant _windows_ and _linux_, meaning the game can be compiled and run on those different operating systems while maintaining smooth network functionality.

## Contributing

Contributions to the R-Type project are welcome! You can report any bugs or request new features via the [issue tracker](https://github.com/yourusername/r-type/issues). To start developing, clone the repository and follow the setup instructions above.

