/* terminal colors */
/* https://en.wikipedia.org/wiki/List_of_colors */
static const char* termcolors[] = {
    "grey50",               //neutral
    "grey31",               //neutral
    "slategray",            //neutral
	"#36454F",              //neutral (charcoal)
	"#98817B",              //neutral (cinereous)
    "blue",                 //cool  - blue
    "darkcyan",             //cool  - blue
    "midnightblue",         //cool  - blue
    "blueviolet",           //cool  - blue
    "cadetblue",            //cool  - blue
	"#2a52be"               //cool  - blue (cerulean)
    "maroon",               //warm  - purple
    "orchid",               //cool  - purple
	"#4B0082",              //cool  - purple (indigo)
	"#703642",              //cool  - purple (catawba)
    "chocolate4",           //warm  - brown
    "darkkhaki",            //warm  - brown
    "darkorange2",          //warm  - orange
    "darkgreen",            //cool  - green
    "seagreen",             //cool  - green
    "forestgreen",          //cool  - green
    "chartreuse",           //cool  - green
	"#78866B",              //cool  - green (camoflage green)
    "gold4",                //warm  - yellow
    "yellow4",              //warm  - yellow
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
