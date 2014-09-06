/* terminal colors */
static const char* termcolors[] = {
    "grey21",               //neutral
    "darkorange2",          //warm  - orange
    "blue",                 //cool  - blue
    "gold4",                //warm  - yellow
    "darkgreen",            //cool  - green
    "chocolate4",           //warm  - brown
    "darkcyan",             //cool  - blue
    "yellow4",              //warm  - yellow
    "seagreen",             //cool  - green
    "sienna4",              //warm  - brown
    "midnightblue",         //cool  - blue
    "maroon",               //warm  - purple
    "forestgreen",          //cool  - green
    "blueviolet",           //cool  - blue
    "darkkhaki",            //warm  - brown
    "orchid",               //cool  - purple
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

    n = r & 0xf;
    if (p == n)
        n = (n + 1) & 0xf;
    p = n;

    if(fork() == 0) {
        if(dpy)
            close(ConnectionNumber(dpy));
        setsid();
        /* choose the color for the terminal and paste it in as the 2nd to last
         * argument */

        /* if we're sure that LENGTH(termcolors) == 16, we can throw out the % */
        /* termcmd[4] = termcolors[(r & 0xf) % LENGTH(termcolors)]; */
        termcmd[4] = termcolors[n];
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
