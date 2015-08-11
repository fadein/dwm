/* See LICENSE file for copyright and license details. */

/* appearance */
//static const char font[]            = "-misc-dejavu sans mono-medium-r-normal--0-0-0-0-m-0-iso8859-1";

// Luxi Sans
//static const char font[]            = "-*-luxi sans-*-r-*-*-*-*-*-*-*-*-*-*";

// Droid Sans Mono
//static const char font[]            = "-*-droid sans mono-*-*-*-*-*-*-*-*-*-*-*-*";

// Droid Sans
//static const char font[]            = "-*-droid sans-medium-*-*-*-*-*-*-*-*-*-*-*";

// Ubuntu Sans
static const char font[]            = "-*-ubuntu-medium-r-*-*-*-*-*-*-*-*-*-*";


static const char normbordercolor[] = "#7f7f7f";
static const char selbordercolor[]  = "#393939";

static const char normfgcolor[]     = "#dfdfdf";
static const char normbgcolor[]     = "#595959";

static const char selfgcolor[]      = "#dfdfdf";
static const char selbgcolor[]      = "#7f7f7f";

static const char urgbordercolor[]  = "#ff0000";
static const char urgbgcolor[]      = "#ffffff";
static const char urgfgcolor[]      = "#ff0000";

static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3",
	"4", "5", "6"
	//"r", "g", "b", "c", "m", "y"
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* graphics */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
	{ "Inkscape", NULL,       NULL,       1 << 2,       False,       -1 },
	{ "MPlayer",          "xv",       "MPlayer",       0,            True,        -1 },
	{ "Display",          "display",  NULL,            0,            True,        -1 },
	{ "feh",              NULL,       NULL,            0,            True,        -1 },

	/* browsers */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Firefox",  NULL,       NULL,       1 << 5,       False,       -1 },
	{ "Xombrero", NULL,       NULL,       1 << 5,       False,       -1 },

	/* terminology - another presentation-specific config */
	{ "terminology", NULL,       NULL,       1 << 3,       False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

#include "gaplessgrid.c"
#include "bstack.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle },    /* first entry is default */
	{ "[]=",      tile },       /* no layout function means floating behavior */
	{ "><>",      NULL },
	{ "###",      gaplessgrid },
	{ "TTT",      bstack },
};

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, "-p", "cmd>" , NULL };
static const char term[] = "urxvtc";
static const char *termcmd[]  = { term, "-sh", "50", "-tint", "white", NULL };

static const char *sudocmd[]     = { term, "-sh", "50", "-tint", "red", "-e", "sudo", "-i", NULL };
static const char *lockcmd[]     = { "slock", NULL };
static const char *killcmd[]     = { "xkill", NULL };

static const char *batterycmd[]  = { "pkill", "-SIGUSR1", "dwm_statusbar", NULL };
static const char *loadavecmd[]  = { "pkill", "-SIGUSR2", "dwm_statusbar", NULL };

static const char *coloncmd[]  = { "pkill", "-SIGHUP",   "dwm_statusbar", NULL };
static const char *minuscmd[]  = { "pkill", "-SIGQUIT",  "dwm_statusbar", NULL };
static const char *gravecmd[]  = { "pkill", "-SIGWINCH", "dwm_statusbar", NULL };
static const char *semiccmd[]  = { "pkill", "-SIGURG",   "dwm_statusbar", NULL };
static const char *pluscmd[]   = { "pkill", "-SIGPOLL",  "dwm_statusbar", NULL };

static const char *nextwall[]    = { "/home/fadein/.wallpapers/cycle/next-wallpaper.sh", NULL };
static const char *prevwall[]    = { "/home/fadein/.wallpapers/cycle/next-wallpaper.sh", "-p", NULL };

static const char *cmusprev[]  = { "cmus-remote", "-r", NULL };
static const char *cmusplay[]  = { "cmus-remote", "-p", NULL };
static const char *cmuspause[] = { "cmus-remote", "-u", NULL };
static const char *cmusstop[]  = { "cmus-remote", "-s", NULL };
static const char *cmusnext[]  = { "cmus-remote", "-n", NULL };

#include "cycletermcolors.c"

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_z,      spawn,          {.v = cmusprev } },
	{ MODKEY,                       XK_x,      spawn,          {.v = cmusplay } },
	{ MODKEY,                       XK_c,      spawn,          {.v = cmuspause } },
	{ MODKEY,                       XK_v,      spawn,          {.v = cmusstop } },
	{ MODKEY,                       XK_b,      spawn,          {.v = cmusnext } },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ 0,                            XK_Menu,   spawn,          {.v = dmenucmd } },

	{ MODKEY,                       XK_period, spawn,           {.v = nextwall } },
	{ MODKEY,                       XK_comma,  spawn,           {.v = prevwall } },
	{ MODKEY|ShiftMask,             XK_Return, randomtermcolors, {0} },

	{ MODKEY,                       XK_s,      spawn,          {.v = sudocmd } },
	{ MODKEY,                       XK_w,      hideMouse,      {0} },

	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },

	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },

	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },

	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_9,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_9,      tag,            {.ui = ~0 } },
	//{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	//{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	//{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	//{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_0,                      0)
	TAGKEYS(                        XK_1,                      1)
	TAGKEYS(                        XK_2,                      2)
	TAGKEYS(                        XK_3,                      3)
	TAGKEYS(                        XK_4,                      4)
	TAGKEYS(                        XK_5,                      5)
	// TAGKEYS(                        XK_6,                      6)
	// TAGKEYS(                        XK_7,                      7)
	// TAGKEYS(                        XK_8,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      reexec,         {0} },

	{ MODKEY,                       XK_a,      spawn,          {.v = batterycmd } },
	{ MODKEY|ShiftMask,             XK_a,      spawn,          {.v = loadavecmd } },

	{ MODKEY|ShiftMask,             XK_equal,  spawn,          {.v = pluscmd  } }, // add one minute
	{ MODKEY|ShiftMask,             XK_colon,  spawn,          {.v = semiccmd } }, // toggle pause/run
	{ MODKEY,                       XK_colon,  spawn,          {.v = coloncmd } }, // toggle visibility of countdown timer
	{ MODKEY,                       XK_grave,  spawn,          {.v = gravecmd } }, // reset sequence #1
	{ MODKEY,                       XK_minus,  spawn,          {.v = minuscmd } }, // reset sequence #2 - reset timer to begining

	{ MODKEY|ControlMask|ShiftMask, XK_k,      spawn,          {.v = killcmd } },
	{ MODKEY|ControlMask,           XK_l,      spawn,          {.v = lockcmd } },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        randomtermcolors, {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

