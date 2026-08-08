<div align="center">

# Varicle Framework

*How I spend my free time? Coding my own engine, of course.*

<img src="assets/bird.png" width="220" alt="Varicle Logo / Mascot" />

---

</div>

Varicle is an opinionated, lightweight game framework built on top of C++ libraries like **[raylib](https://www.raylib.com/)** and **[EnTT](https://github.com/skypack/entt)**. 

It's primarily a personal playground—a collection of random features, architecture experiments, and side projects thrown together while I figure out what I want to build with it.

---

### ⚠️ A Quick Heads-Up

* **Expect redundancy:** Some parts of the engine may be over-engineered, redundant, or unused. That's just what happens when you're experimenting!
* **Will it ever be a complete engine?** *I have no idea.*

---

## 🛠️ Stack & Dependencies

| Tool | Purpose |
| :--- | :--- |
| **raylib** | Windowing, graphics API, input, and audio |
| **EnTT** | Entity Component System (ECS) architecture |

---

## 🚀 Getting Started


### Building for Desktop

```bash
# 1. Create project directory and clone Varicle
mkdir my-game
cd my-game
git clone --recurse-submodules https://github.com/ShadesAndGrays/varicle-framework.git varicle

# 2. Copy the CMake template and starter source files
cp varicle/template/CMakeLists.txt .
cp -r varicle/examples/basic-example/src .

# 3. Configure and build
cmake -B build/desktop -DCMAKE_BUILD_TYPE=Release -DBUILD_EXAMPLES=OFF
cmake --build build/desktop

# 4. Launch the game executable
./build/desktop/my-game.exe
```

### Building for web

```bash
# 1. Configure and build using Emscripten
emcmake cmake -B build/web -DCMAKE_BUILD_TYPE=Release -DBUILD_EXAMPLES=OFF
cmake --build build/web

# 2. Start a local web server
python -m http.server 8080

# 3. Open http://localhost:8080 in your browser
```


