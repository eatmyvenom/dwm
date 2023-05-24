/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;
static const unsigned int snap      = 4;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Fira Code:size=10" };


static const int usealtbar          = 1;        /* 1 means use non-dwm status bar */
static const char *altbarclass      = "Polybar"; /* Alternate bar class name */
static const char *alttrayname      = "tray";    /* Polybar tray instance name */
static const char *altbarcmd        = "return 0"; /* Alternate bar launch command */

static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 20;       /* vert inner gap between windows */
static const unsigned int gappoh    = 20;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 20;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */

/* unneeded because i use rofi */
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#0066cc"; // venom - blue that matches my terminal
static const char col_border[]      = "#000000";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_border },
	[SchemeSel]  = { col_gray4, col_cyan,  col_border  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.51; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[\\]",     dwindle },                // 0
	{ "[M]",      monocle },                // 1
	{ "[@]",      spiral },                 // 2
	{ "[]=",      tile },                   // 3
	{ "H[]",      deck },                   // 4
	{ "TTT",      bstack },                 // 5
	{ "===",      bstackhoriz },            // 6
	{ "HHH",      grid },                   // 7
	{ "###",      nrowgrid },               // 8
	{ "---",      horizgrid },              // 9
	{ ":::",      gaplessgrid },            // 10
	{ "|M|",      centeredmaster },         // 11
	{ ">M>",      centeredfloatingmaster }, // 12
	{ "><>",      NULL },                   // 13
	{ NULL,       NULL },                   // 14
};
// venom - make meta/windows key main modifier and alt only used for alt+tab
#define USE_WINKEY 1

#ifdef USE_WINKEY
	#define MODKEY Mod4Mask
	#define ALTKEY Mod1Mask
#endif
#ifndef USE_WINKEY
	#define MODKEY Mod1Mask
	#define ALTKEY Mod1Mask
#endif
// end venom


#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },


#include "unfloat.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_b,      togglebar,      {0} },

	{ MODKEY,                       XK_Up,     focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Down,   focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Right,  focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Left,   focusstack,     {.i = -1 } },

	{ MODKEY,                       XK_minus,  incrgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  incrgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_equal,  incrgaps,        {.i = gappoh } },

	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[13]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_d,      setlayout,      {.v = &layouts[7]} },

	{ MODKEY,                       XK_space,  unfloatvisible, {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

void
setlayoutex(const Arg *arg)
{
	setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void
viewex(const Arg *arg)
{
	view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
	view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
	toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
	tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
	toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
	tag(&((Arg){.ui = ~0}));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum           function */
	{ "focusstack",     focusstack },
	{ "setmfact",       setmfact },
	{ "togglebar",      togglebar },
	{ "incnmaster",     incnmaster },
	{ "togglefloating", togglefloating },
	{ "focusmon",       focusmon },
	{ "tagmon",         tagmon },
	{ "zoom",           zoom },
	{ "view",           view },
	{ "viewall",        viewall },
	{ "viewex",         viewex },
	{ "toggleview",     view },
	{ "toggleviewex",   toggleviewex },
	{ "tag",            tag },
	{ "tagall",         tagall },
	{ "tagex",          tagex },
	{ "toggletag",      tag },
	{ "toggletagex",    toggletagex },
	{ "killclient",     killclient },
	{ "quit",           quit },
	{ "setlayout",      setlayout },
	{ "setlayoutex",    setlayoutex },
	{ "setgaps",        setgaps },
};