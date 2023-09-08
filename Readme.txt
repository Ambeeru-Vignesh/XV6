# XV6

Implementing uniq on xv6 as user program Steps:

1. created demo.txt file, which has following content.
   • I understand the Operating system.
   • I understand the Operating system.
   • I understand the Operating system.
   • I love to work on OS.
   • I love to work on OS.
   • Thanks xv6.

2. created a file called uniq.c which contains the logic for removing the adjacent duplicate line from a file. Please find file in the attached documents. The code is written using extensive c libraries.

upon executing this file it produces desirable results as it is shown in the below screenshot.

![desirable output](<images/gcc output.png>)

3. Later, I have decided to run this in the qemu environment, I have created a fie called example.txt which holds same information as demo.txt. I have included both example.txt and uniq.c(modified verion which supports xv6, **THE LOGIC HOLDS SAME**) in Makefile.png as you can see below. I'm attaching new uniq.c code and example.txt.

![example.txt](images/example.txt.png)
![uniq.c](images/uniq.c.png)
![uniq.c code continuation](<images/uniq.c(2).png>)
![Makefile](images/Makefile.png)

4. After running commands "make" and "make qemu", I have successfully entered the qemu environment and run ls command to confirm that I have all the required files. As you can see below, I have all necessary files.

![Files list](<images/Qemu env files.png>)

5. After running the command "uniq example.txt", I can see that the duplicate lines are not removed irrespective of having same logic. I have tried taking assistance from internet and all possible resources I have access to, but I couldn't fix this.

![The Output](<images/uniq example.txt.png>)

**Please let me know if I missed anything or if there is anything more I should have added. Also, let me know why, when I run the program again using gcc, I am able to view the required result but not when I use qemu, even though the logic is the same in both cases.**
