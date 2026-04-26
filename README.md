#  GetToSpace

> *A cube. A dream. The stars.*

A 2D platformer written in **pure C** using [raylib](https://www.raylib.com/), where you guide a colorful cube through increasingly challenging levels on its way to the stars.

> ⚠️ **Beta Release** — Bugs are expected! Feedback is very welcome. More levels (and first bossfight) will come soon!

---

##  Gameplay

You play as Cube with one big dream: getting to space.  
Work your way through the levels,  and make it to the rocket that'll take you there (currently not implemented, sorry...).

An auto-converted Web version: [Here](https://therealallinone.itch.io/gettospace)


---

##  Levels as of 26.04.2026

| # | Name | Description |
|---|------|-------------|
| 0 | Intro | Meet Cube |
| 1 | Level 1 | First steps |
| 1-2 | Level 1-2 | Stars are everywhere |
| 2 | Level 2 | Mind the gap |
| 2-2 | Level 2-2 | Three platforms, one path |
| 3 | Level 3 | Obstacles enter the picture |
| 4 | Level 4 | Platforming gets serious |
| 5 | Level 5 | Danger zones |
| 6 | Level 6 | Boost pads |

Progress is automatically saved. You can replay any unlocked level via the **Level Select** menu.

---

##  Controls

| Key | Action |
|-----|--------|
| `A` | Move left |
| `D` | Move right |
| `W` | Jump (only when grounded) |

---

## 🛠️ Building

### Dependencies

- [raylib](https://github.com/raysan5/raylib) (including `raymath.h`!)
- GCC or Clang
- Linux

### Compile

```bash
gcc -o GetToSpace RayLib.c -lraylib -lm
```

Make sure `raylib` is installed on your system. On Debian/Ubuntu:

```bash
sudo apt install libraylib-dev
```

### Run

```bash
./GetToSpace
```

The game expects an `images/` folder in the same directory as the binary, containing:
- `Vol1.png` — background image
- `Star.png` — star/goal texture
- The other images for better graphics/ The first Boss is currently unused.

---

##  Save System

Progress is stored at:

```
~/.GetToSpace/saves/save.dat
```

>  Manually editing this file will corrupt your save.

---

##  License

MIT

---

##  Credits

- [raylib](https://www.raylib.com/) — the fantastic C game library powering this project
- [HackClub](https://hackclub.com/) — for the motivation to ship
- Claude & GitHub Copilot — for helping unstick the stuck moments
- **You** — for playing ❤️

---

*Made with ☕☕☕ and way too much raylib documentation by [TheSkriptKid](https://github.com/TherealONE12)*
