# 🐍 Snake Game

## 🧩 Description

This project is a custom version of the famous **Snake** game.  
It features the classic rules — eat food, grow longer, avoid walls and yourself — with some additional features like **random color food** and **smooth rendering** using **SFML**.

---

## 🧰 Software Requirements

To ensure the game compiles correctly, make sure the following software is installed on your system:

| Software | Minimum Version | Description |
|-----------|------------------|-------------|
| **g++**   | 2.28             | C++ compiler |
| **CMake** | 3.28.3           | Build configuration tool |
| **SFML**  | 2.6.1            | Graphics and multimedia library |
| **Make**  | 4.3              | Build automation tool |

---

## ⚙️ Software Installation (Debian / Ubuntu)

```bash
sudo apt update
sudo apt upgrade -y

sudo apt install g++      # or build-essential
sudo apt install cmake
sudo apt install libsfml-dev
sudo apt install make
```

---

## 🧱 Manual Compilation

To build and run the project manually (without VS Code):

```bash
# Clean and build
make clean 
make build
```

If you want to switched between regular or random color snake, you can use this command:
```bash
# Regular snake
make regular
# Random color snake
make color
```
To lunch the game, you can use this command:
```bash
# Lunch the game
make
```

---

## 🧩 Compilation with VS Code

1. Install the following extensions:
   - **C/C++** (by Microsoft)
   - **CMake Tools**
   - **Code Runner** (optional)

2. Open the project folder in VS Code.

3. Select your CMake kit (bottom bar → “No active kit” → choose `GCC` or similar).

4. Run the build:
   - `Ctrl + Shift + P` → type `CMake: Build`
   - Or use the **Build** button in the status bar.

5. Run the game:
   - `Ctrl + F5` or the **Run ▶️** icon.

---

## 🎮 Game Controls

| Key | Action |
|-----|---------|
| **↑**  | Move up |
| **↓** | Move down |
| **←** | Move left |
| **→** | Move right |
| **SPACE** | Pause/Unpause the game|




---

## 💡 Notes

- The game uses **SFML** for rendering and input handling.
- You can change snake and food skin in the folder `colors/assets`.
- Default configuration files are in the `include/` and `colors/` folders.

---

## 🧑‍💻 Author

- **Simon CRUCHET**

---