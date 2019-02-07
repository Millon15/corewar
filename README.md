# corewar

## ```Corewar``` is a School 42 project. It is the final project of the Algorithms branch

### The purpose of this project is an implementation of the programming game “Core War”

_Done by two ~~awesome~~ restless individuals:_  
[me](https://github.com/ArtemisKS) & Vitas Brazas (aka [millon15](https://github.com/millon15))

---

## Project Structure

This project consists of five parts:

- ```Champion```
- ```Assembler```
- ```Virtual Machine(THE ARENA)```
- ```Visualizer```

Project has one developed champion: `bot_kompot.s`. It is located in the project's root directory.

Assembler is the module of program `asm`

Virtual Machine + Visualizer are modules of program `corewar`

---

## Cloning the repo & installation

This repository includes submodule. So if you want to clone it, you can use the following command:

```git clone --recurse-submodules <repository url>```

To get the executables `asm` & `corewar`, simply run ```make```

---

## Usage

### `asm`

```
Usage: ./asm champion.cor
```

### `Corewar`

```
Usage: ./corewar [-v N] [(-d|-dump) N] [--ncurses [--stealth] [--start-in N] [(--venom|--skibidi)]] [-n N champion.cor] <champion1.cor> <...>
	(-d|-dump) N		: dumps memory after N cycles then exits
	--ncurses		: ncurses output mode
				--start-in N	: waits N cycles, then starts the ncurses mode
				--stealth	: hides the real contents of the memory in ncurses mode
				--no-stat	: turn off stat(3rd) window in ncurses mode
				--(venom|skibidi|bigshaq) : playing last chosen sounds in ncurses mode
	-n N champion.cor	: sets the N of the next player
	-v N			: verbosity levels, can be added together to enable several
				- 0	: Show only essentials
				- 1	: Show lives
				- 2	: Show cycles
				- 4	: Show operations (Params are NOT litteral ...)
				- 8	: Show deaths
```

---

## Visualisation

The best visualizer performance is with iTerm (make sure you've got the latest version).

```Random bots combination midgame screenshot```

![CoreWar screenshot #1](/images/CoreScreen.png)

```Random bots combination endgame screenshot```

![CoreWar screenshot #2](/images/CoreScreenFinal.png)

---

## That's all, guys, hope you enjoyed it😉
