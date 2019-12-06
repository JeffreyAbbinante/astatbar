# astatbar
About:
astatbar is a statusbar replacement for dwm

Contributing:
There is still a ton of work to be done.
Although this isn't designed to be an advanced statusbar, I want this to be usable for most people.
Please provide pull requests and feedback for my consideration.

Installing:
1. Download the file corresponding to your computer.
2. Run the following command: gcc -std=c99 -O3 -march=native -flto -o ~/.astatbar astatbar*.c //passing -O3, -march=native, and -flto are optional but could slightly improve the speed of the program.
3. Add the following to your .xinitrc: 
while true; do
  xsetroot -name "$(./.astatbar)"
done &
4. Reload dwm.
