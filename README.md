
# P2PMessenger

A lightweight peer-to-peer (P2P) messaging application built in C++ that enables local peer discovery and real-time communication without relying on internet connectivity. Perfect for offline or LAN-based communication.

## ✨ Features

- 🔍 Local peer discovery using UDP broadcasting
- 📬 Real-time message exchange over TCP sockets
- 🪟 Simple text-based user interface (CLI)
- 🪟 Built and tested on Windows using CLion and MinGW
- 💬 Modular codebase for sender and receiver support

---

## 📂 Project Structure

```
P2PMessenger/
├── CMakeLists.txt
├── main.cpp            # Entry point of the application
├── peer.cpp            # Contains initDiscovery() and startServer()
├── peer.h              # Header declarations for peer functions
├── ui.cpp              # Contains runUI() for text-based UI
├── ui.h                # Header for UI functions
```

---

## ⚙️ Prerequisites

- **OS:** Windows
- **IDE:** [CLion](https://www.jetbrains.com/clion/)
- **Compiler:** [MinGW with g++](https://sourceforge.net/projects/mingw/)
- **CMake** (bundled with CLion)



## 🛠️ Installation

1. **Clone the Repository**

   ```bash
   git clone https://github.com/your-username/P2PMessenger.git
   cd P2PMessenger
   ```

2. **Open in CLion**

   - Launch CLion
   - Click on `Open` and select the `P2PMessenger` folder
   - CLion will automatically detect the `CMakeLists.txt` file

3. **Setup MinGW in CLion**

   - Go to **File > Settings > Build, Execution, Deployment > Toolchains**
   - Set `C Compiler` and `C++ Compiler` paths to your MinGW `gcc.exe` and `g++.exe`
   - Click Apply and wait for CMake to configure



## 🚀 How to Run

1. **Build the Project**

   - Go to **Build > Build Project** or press `Ctrl + F9`

2. **Run the Application**

   - Go to **Run > Run 'main'** or press `Shift + F10`
   - The application will initialize WSA, start the server, and launch the UI

3. **Test with Two Instances**

   - Run the application on two terminals or two different PCs on the same network
   - Use the UI to send messages between peers



## 🔧 Customization

- Modify `peer.cpp` to adjust UDP broadcast settings
- Customize CLI UI in `ui.cpp` to suit your theme



## 📦 Building Without CLion (Optional)

If you want to build using command line:

```bash
g++ main.cpp peer.cpp ui.cpp -lws2_32 -o P2PMessenger.exe
```

Make sure `MinGW` is added to your PATH and use `-lws2_32` to link Windows Sockets API.




## 🙌 Contributing

Contributions are welcome! Please feel free to:

- Fork the repo
- Create a new branch
- Submit a pull request



## 👨‍💻 Author

Built with ❤️ by [@animex007](https://github.com/animex007)

