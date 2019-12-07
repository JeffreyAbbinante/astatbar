# astatbar
About:
astatbar is a statusbar replacement for dwm

Contributing:
There is still a ton of work to be done. Although this is not designed to be an advanced statusbar, I want this to be usable for most people. Please provide pull requests and feedback for my consideration.

To Do/Wishlist:
* Configuration File
* Unified Source File
* Volume Support
* Network Detection
* Easier say to move statusbar elements around without extensive source code editing.
* Setting root window without xsetroot
* OpenBSD support

Installing:
1. Download the file corresponding to your computer.
2. Run the following command: 

GCC (Linux):
```
gcc -std=c99 -O3 -march=native -flto=$(nproc) -o ~/.astatbar astatbar*.c
```
Clang (OpenBSD):
```
clang -std=c99 -O3 -march=native -o ~/.astatbar astatbar*.c
```

Note: Passing -O3, -march=native, and -flto are optional but could slightly improve the speed of the program.

3. Add the following to your .xinitrc (Linux) or .xsession (OpenBSD): 
```
while true; do
  xsetroot -name "$(./.astatbar)"
  sleep 1
done &
```
Note: Set sleep to the frequency you want the statusbar to refresh. In this example, it is once per second.

4. Reload dwm.
