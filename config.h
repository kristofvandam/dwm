/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;       /* border pixel of windows */
static const unsigned int gappx     = 15;      /* gaps between windows */
static const unsigned int snap      = 32;      /* snap pixel */
static const int showbar            = 1;       /* 0 means no bar */
static const int topbar             = 1;       /* 0 means bottom bar */
static const int vertpad            = 0;       /* vertical padding of bar */
static const int sidepad            = 0;       /* horizontal padding of bar */
static const char *fonts[]          = { "DroidSansMono:size=14" };
static const char dmenufont[]       = "DroidSansMono:size=14";
static const char col_white[]       = "#9d9d9d";
static const char col_black[]       = "#000000";
static const char col_primary[]     = "#2d2d2d";
static const char col_selected[]    = "#ede480"; /*green: oob7ed24*/
static const char col_unselected[]  = "#2d2d2d";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#2D2D2D";
static const char *colors[][3]      = {
	/*               	 fg          bg               border   */
	[SchemeNorm]     = { col_white , col_primary    , col_white   } ,
	[SchemeSel]      = { col_black , col_cyan       , col_white   } ,
	[SchemeStatus]   = { col_white , col_primary    , "#000000"   } , // Statusbar right {text            , background , not used but cannot be empty }
	[SchemeTagsSel]  = { col_black , col_selected   , "#000000"   } , // Tagbar left selected {text       , background , not used but cannot be empty }
	[SchemeTagsNorm] = { col_white , col_unselected , "#000000"   } , // Tagbar left unselected {text     , background , not used but cannot be empty }
	[SchemeInfoSel]  = { col_white , col_cyan       , "#009900"   } , // infobar middle  selected {text   , background , not used but cannot be empty }
	[SchemeInfoNorm] = { col_white , col_primary    , "#000000"   } , // infobar middle  unselected {text , background , not used but cannot be empty }
};

/* tagging */
static const char *tags[] = { "TERM", "DEV", "BROWSE", "MISC" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Tilix",    NULL,       NULL,       0,            0,           -1 }, 
	{ "Sublime",  NULL,       NULL,       1 << 1,       0,           -1 }, 
	{ "Firefox",  NULL,       NULL,       1 << 2,       0,           -1 },
	{ "Gimp",     NULL,       NULL,       1 << 3,       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[R]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[C]",      col },	
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

static const char *dmenucmd[]        = { 
	"dmenu_run",
	"-m", dmenumon,
	"-fn", dmenufont,
	"-nb", col_primary,
	"-nf", col_gray3,
	"-sb", col_cyan,
	"-sf", col_gray4,
NULL };

static const char *rofiruncmd[]         = { 
	"rofi",
	"-show", "run",
	"-theme", "/home/kristof/Projects/rice/dwm/slate.rosi",
NULL };
static const char *rofiwindowcmd[]         = { 
	"rofi",
	"-show", "window",
	"-theme", "/home/kristof/Projects/rice/dwm/slate.rosi",
NULL };
static const char *brightness_up[]   = { "xbacklight", "-inc", "10", NULL };
static const char *brightness_down[] = { "xbacklight", "-dec", "10", NULL };
static const char *termcmd[]         = { "alacritty", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ 0,                            0x1008ff02,spawn,          {.v = brightness_up } },
	{ 0,                            0x1008ff03,spawn,          {.v = brightness_down } },
	{ MODKEY,                       XK_p,      spawn,          {.v = rofiruncmd } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = rofiwindowcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },	
	TAGKEYS(                        XK_ampersand,              0)
	TAGKEYS(                        XK_eacute,                 1)
	TAGKEYS(                        XK_quotedbl,               2)
	TAGKEYS(                        XK_apostrophe,             3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_agrave,                 9)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

