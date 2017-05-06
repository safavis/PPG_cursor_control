Kindly read the following link for understanding how to program boot image into ezdsp
http://processors.wiki.ti.com/index.php/C5515_Boot-Image_Programmer

High level overview of the process:
1. Convert your <program_name>.out to <program_name>.bin using the hex utility
2. Load the programmar code into the ezdsp board and run it
3. Give the path to your <program_name>.bin file