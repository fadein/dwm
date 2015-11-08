/* terminal colors */
/* https://en.wikipedia.org/wiki/List_of_colors */

/* use this shell function to test different settings:
 * The contents of file mg.txt is given in the #if 0 block below
 * colortest () {
 *         urxvt -sh 50 -tint "$1" -e sh -c "figlet -f small '$1'; cat mg.txt; while true; do read; done" &
 *         }
 */
static const char* termcolors[] = {
    "grey50",               //neutral
    //"grey31",               //neutral -- not interesting enougk
    //"slategray",            //neutral -- not interesting enougk
    "#36454F",              //neutral (charcoal)
    "#98817B",              //neutral (cinereous)

    "blue",                 //cool  - blue
    //"darkcyan",             //cool  - blue -- hard to read
    "midnightblue",         //cool  - blue
    //"blueviolet",           //cool  - blue -- hard to read
    "cadetblue",            //cool  - blue
    //"#2a52be",              //cool  - blue (cerulean) -- hard to read

    //"orchid",               //cool  - purple -- hard to read
    "#4B0082",              //cool  - purple (indigo)
    "#703642",              //cool  - purple (catawba)
    //"maroon",               //warm  - purple -- hard to read

    "chocolate3",           //warm  - brown
    //"darkkhaki",            //warm  - brown -- hard to read

    //"darkorange2",          //warm  - orange -- too close to chocolate3

    "darkgreen",            //cool  - green
    "seagreen",             //cool  - green
    // "forestgreen",          //cool  - green -- too close to other greens
    // "chartreuse",           //cool  - green -- too hard to read
    "#78866B",              //cool  - green (camoflage green)

    "gold3",                //warm  - yellow
    //"yellow4",              //warm  - yellow -- too close to gold3
};

/* Cycle through the colors in order */
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

/* pick a color at random */
void
randomtermcolors(const Arg *arg) {
#define SHIFT_BY 4
#define BITS_IN_A_BYTE 8
    static unsigned long long r = 0; /* store the random data from urandom */
    static unsigned t = 0;           /* keep track of when we need to grab new data */
    static unsigned short n, p = -1;

    /* read another byte from /dev/urandom */
    if (t == 0) {
        FILE *urand = fopen("/dev/urandom", "r");
        if (urand == NULL || fread(&r, 1, sizeof(r), urand) < sizeof(r))
            r = 0x9a92e5b988a3d8f2;
        if (urand)
            fclose(urand);
        t = sizeof(r) * BITS_IN_A_BYTE / SHIFT_BY;
    }

    // use the last 4 bits of our random number as an index
    n = (r & 0xf) % LENGTH(termcolors);
    if (p == n)
        n = ((n + 1) & 0xf) % LENGTH(termcolors);
    p = n;

    if(fork() == 0) {
        if(dpy)
            close(ConnectionNumber(dpy));
        setsid();
        /* scan the arguments for they keyword "white"
         * choose a random color for the terminal and paste it in 
         * over the "REPLACE ME" argument */

        /* if we're sure that LENGTH(termcolors) == 16, we can throw out the % */
        /* termcmd[4] = termcolors[(r & 0xf) % LENGTH(termcolors)]; */
        int i;
        for (i = 0; termcmd[i]; ++i)
            if (! strncmp("white", termcmd[i], 5))
                break;
        termcmd[i] = termcolors[n];
        execvp(termcmd[0], (char* const*)termcmd);
        fprintf(stderr, "dwm: execvp %s", termcmd[0]);
        perror(" failed");
        exit(EXIT_SUCCESS);
    }
    else {
        /* how far to shift this? enough bits to address anything in the colors array...*/
        r >>= SHIFT_BY;
        --t;
    }
}


#if 0
[0;37;49m  [0;33;49m|[0;37;49m  [0;37;49m([0;36;49m'[0;37;49m)[0;36;49m'[0;37;49m)[0;37;49m     [0;31;49m/[0;37;49m    [0;31;49m\|[0;37;49m [0;31;49m|[0;37;49m [0;31;49m|[0;37;49m [0;31;49m|/[0;37;49m [0;31;49m_`[0;37;49m [0;31;49m|/[0;37;49m [0;31;49m_`[0;37;49m [0;31;49m|[0;37;49m [0;31;49m|/[0;37;49m [0;31;49m_[0;37;49m [0;31;49m\[0;37;49m           [0;34;49m/[0;37;49m [0;35;49m_[0;37;49m(([0;33;49m\[0;36;49m-[0;37;49m [0;36;49m-[0;33;49m/[0;37;49m))[0;35;49m_[0;37;49m [0;34;49m\[0;37;49m     
  [0;33;49mC[0;37;49m     [0;33;49m_)[0;37;49m    [0;31;49m/[0;37;49m [0;31;49m/\/\[0;37;49m [0;31;49m\[0;37;49m [0;31;49m|_|[0;37;49m [0;31;49m|[0;37;49m [0;31;49m(_|[0;37;49m [0;31;49m|[0;37;49m [0;31;49m(_|[0;37;49m [0;31;49m|[0;37;49m [0;31;49m|[0;37;49m  [0;31;49m__/[0;37;49m           [0;34;49m\[0;37;49m [0;35;49m\[0;37;49m())[0;33;49m([0;31;49m-[0;33;49m)[0;37;49m(()[0;35;49m/[0;37;49m [0;34;49m/[0;37;49m     
   [0;33;49m\[0;37;49m   [0;31;49m_[0;33;49m|[0;37;49m     [0;31;49m\/[0;37;49m    [0;31;49m\/\__,_|\__,[0;37;49m [0;31;49m|\__,[0;37;49m [0;31;49m|_|\___|[0;37;49m            [0;34;49m'[0;37;49m [0;35;49m\[0;37;49m(((()))[0;35;49m/[0;37;49m [0;34;49m'[0;37;49m      
    [0;33;49m\__/[0;37;49m                    [0;31;49m|___/[0;37;49m [0;31;49m|___/[0;37;49m                   [0;34;49m/[0;37;49m [0;35;49m'[0;37;49m [0;35;49m\[0;37;49m))[0;35;49m.[0;37;49m))[0;35;49m/[0;37;49m [0;35;49m'[0;37;49m [0;34;49m\[0;37;49m     
   [0;31;49m<___[0;37;49mY[0;31;49m>[0;37;49m                                                [0;34;49m/[0;37;49m [0;34;49m_[0;37;49m [0;35;49m\[0;37;49m [0;35;49m-[0;37;49m [0;35;49m|[0;37;49m [0;35;49m-[0;37;49m [0;35;49m/[0;34;49m_[0;37;49m  [0;34;49m\[0;37;49m    
  [0;31;49m/[0;37;49m  [0;31;49m\[0;37;49m [0;36;49m:[0;31;49m\\[0;37;49m          [0;36;49m_[0;37;49m                to                 [0;34;49m([0;37;49m   [0;33;49m([0;37;49m [0;36;49m.;''';.[0;37;49m [0;33;49m)[0;34;49m'[0;37;49m  [0;34;49m)[0;37;49m   
   [0;33;49m\[0;37;49m [0;33;49m\[0;33;49m==[0;35;49mL|[0;37;49m  [0;33;49m\\\[0;37;49m         [0;36;49m)[0;37;49m  [0;36;49m)[0;37;49m  [0;36;49m)[0;37;49m [0;36;49m||[0;37;49m [0;36;49m/\\[0;37;49m [0;36;49m(([0;37;49m [0;36;49m||[0;37;49m  [0;36;49m||[0;37;49m   [0;36;49m||[0;37;49m [0;36;49m||[0;37;49m   [0;34;49m/[0;37;49m [0;35;49m.[0;37;49m   [0;33;49m.[0;37;49m   [0;35;49m.[0;37;49m [0;34;49m\[0;37;49m      
   [0;33;49m///`[0;37;49m [0;34;49m||[0;37;49m             [0;36;49m/-_/-_/[0;37;49m  [0;36;49m\\[0;37;49m  [0;36;49m||[0;37;49m  [0;36;49m\/\\[0;37;49m  [0;36;49m\\,[0;37;49m   [0;36;49m\\/[0;37;49m   [0;34;49m/[0;37;49m   [0;35;49m.[0;37;49m     [0;35;49m.[0;37;49m   [0;34;49m\[0;37;49m     
    [0;34;49m|[0;37;49m   [0;34;49m||[0;37;49m                          [0;36;49m/[0;37;49m                    [0;34;49m/[0;37;49m   [0;35;49m/[0;37;49m   [0;33;49m|[0;37;49m   [0;35;49m\[0;37;49m   [0;34;49m\[0;37;49m    
    [0;34;49m|[0;37;49m   [0;34;49m||[0;37;49m                         [0;36;49m(,[0;37;49m                   [0;34;49m/[0;37;49m   [0;35;49m/[0;37;49m    [0;33;49mb[0;37;49m    [0;35;49m\[0;37;49m   [0;34;49m\[0;37;49m   
    [0;34;49m|[0;37;49m   [0;34;49m||[0;37;49m                                             [0;34;49m/[0;37;49m   [0;35;49m/[0;37;49m     [0;33;49mBb[0;37;49m    [0;35;49m\[0;37;49m   [0;34;49m\[0;37;49m  
    [0;34;49m|[0;37;49m   [0;34;49m||[0;37;49m              [0;32;49m.d[0;37;49m  [0;32;49mdPYYb[0;37;49m                     [0;34;49m/[0;37;49m   [0;35;49m|[0;37;49m      [0;33;49mBBb[0;37;49m    [0;35;49m\[0;37;49m   [0;34;49m\[0;37;49m 
    [0;34;49m[___]][0;37;49m        in  [0;32;49m.d88[0;37;49m [0;32;49mdP[0;37;49m   [0;32;49mYb[0;37;49m                   [0;34;49m(__[0;37;49mmrf[0;35;49m\____[0;33;49m.dBBBb.[0;35;49m__)[0;34;49m___)
[0;37;49mjgs [0;30;49m(____))[0;37;49m             [0;32;49m88[0;37;49m [0;32;49mYb[0;37;49m   [0;32;49mdP[0;37;49m  easy steps                                
                        [0;32;49m88[0;37;49m  [0;32;49mYbodP[0;37;49m                                             
[0m
#endif

/* vim:set expandtab: */
