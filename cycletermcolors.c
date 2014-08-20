/* terminal colors */
static const char* termcolors[] = {
       "grey21",               //neutral
       "darkorange2",  //warm  - orange
       "blue",                 //cool  - blue
       "gold4",                //warm  - yellow
       "darkgreen",    //cool  - green
       "chocolate4",   //warm  - brown
       "darkcyan",             //cool  - blue
       "yellow4",              //warm  - yellow
       "seagreen",             //cool  - green
       "sienna4",              //warm  - brown
       "midnightblue", //cool  - blue
       "maroon",               //warm  - purple
       "forestgreen",  //cool  - green
       "blueviolet",   //cool  - blue
       "darkkhaki",    //warm  - brown
       "orchid",               //cool  - purple
};

void
cycletermcolors(const Arg *arg) {
       static int i = 0;
       if(fork() == 0) {
               if(dpy)
                       close(ConnectionNumber(dpy));
               setsid();
               /* choose the color for the terminal and paste it in as the 2nd to last
                * argument */
               termcmd[4] = termcolors[i];
               execvp(termcmd[0], (char* const*)termcmd);
               fprintf(stderr, "dwm: execvp %s", termcmd[0]);
               perror(" failed");
               exit(EXIT_SUCCESS);
       }
       else {
               /* increment the terminal color */
               i = (i + 1) % LENGTH(termcolors);
       }
}
