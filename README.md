# GBAMorse SOS  :computer::video_games::space_invader::sos:

This project uses GameBoy Developers Kit (GBDK) in order to programming a __Morse SOS__ to Game Boy in C language. The Morse SOS consists of a collection of two ROMs, a _master_ and a _slave_. The Master ROM has a built-in keyboard which players can type a message written in human language and send this message codified in morse language via serial port. The Slave ROM, in this project, receives that codified message and turns it into an acoustic and lighting mourse signal. We truly think Lara Croft, from the Tomb Raider series, would very much appreciate it -- and we hope you feel the same.



## Useful Links

- Our first step took place at a nice community called Awesome Game Boy Development (which is truly awesome!). Check their repository [here](https://github.com/gbdev/awesome-gbdev/blob/master/README.md#documentation).

- [Game Boy Developers Kit (GBDK)](http://gbdk.sourceforge.net/) - use this link to see documentation and sources of GBDK.

- There's a nice newcomers project called _Sheep it Up!_ Check it [here](https://www.gamasutra.com/blogs/DoctorLudos/20171207/311143/Making_a_Game_Boy_game_in_2017_A_quotSheep_It_Upquot_PostMortem_part_12.php).

- There's a lack of Game Boy sound resources over the internet, but these ones helped us a lot:
    - [Chris Strickland's Overview of Audio Programming in Game Boy](https://www.gamedev.net/articles/programming/general-and-gameplay-programming/audio-programming-on-the-gameboy-advance-part-1-r1823/).
    - [Gaming Monsters]((https://www.youtube.com/channel/UCMMhSfBStEti-Lqzs30HYWw/)) have a loooooot of nice tutorials over programming to Game Boy. Their YouTube videos are very useful. We'd strongly recommend to check (all of) them out.

## Compiling

There's already a BAT file to compile from sources, one for the main source (the master) and the slave ROM (in the slave folder). To do that, open a terminal inside the correspondently folder and type:

```
./make.bat
```

You can also just run the make file and it's ready to go -- but terminal helps you with a log to see if everything went fine.

## Tips


We'd reccomend you to use a (very nice) emulator to Game Boy called __BGB__ to test this project. Sources over here. To help you with a quick start, this repository has a folder called _roms_, with the ROMs already built-in. To enable serial port communication between two GBAs, open two BGB's window, right-click on one, then Link -> Listen. Choose a port (you can use default to run on your local machine). After that, right-click on the other one, then Link -> Connect. Choose IP (again, keep default to run on your local machine). Now, load the ROMs and you're okay to go. Follow the instructions on the screen -- they're human-friendly :).

Have fun! :smiley::video_game: