#include <X11/XF86keysym.h>

/* appearance */
static const char font[]            = "-*-tamsynmod-medium-r-*-*-14-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#eee8d5";
static const char normbgcolor[]     = "#fdf6e3";
static const char normfgcolor[]     = "#586e75";
static const char selbordercolor[]  = "#93a1a1";
static const char selbgcolor[]      = "#657b83";
static const char selfgcolor[]      = "#eee8d5";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 8;        /* snap pixel */
static const unsigned int gappx     = 10;        /* useless gap between windows */
static const Bool monoclegap        = True;     /* show gap in monocle and single window mode */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
  /* class                  instance  title       tags mask     isfloating   monitor */
  { NULL,                   NULL,     NULL,       0,            False,       -1 },
  { "Keepassx",             NULL,     NULL,       0,            True,        -1 },
  { "Seafile Client",       NULL,     NULL,       0,            True,        -1 },
  { "seafile-applet",       NULL,     NULL,       0,            True,        -1 },
};

/* layout(s) */
#define MFACT                   0.55
static const float mfact      = MFACT; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;     /* number of clients in master area */
static const Bool resizehints = True;  /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
  /* symbol     arrange function */
  { "[]=",      tile },
  { "[M]",      monocle },
  // { "<><",      NULL }, // no layout -> floating
};

/* scratchpad */
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "termite", "--geometry", "1280x800", "-t", scratchpadname, NULL };

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG)                                                \
  { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
  { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define CMD(...) { .v = (const char*[]) { __VA_ARGS__, NULL} }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "termite", NULL };

static Key keys[] = {
  /* modifier                     key                  function        argument */
  { MODKEY,                       XK_p,                spawn,          {.v = dmenucmd } },
  { MODKEY|ShiftMask,             XK_Return,           spawn,          {.v = termcmd } },
  { MODKEY|ControlMask,           XK_t,                spawn,          {.v = termcmd } },
  { 0,                            XK_F10,              togglescratch,  {.v = scratchpadcmd } },
  { MODKEY,                       XK_o,                spawn,          CMD("networkmanager_dmenu") },
  { MODKEY,                       XK_F12,              spawn,          CMD("systemctl", "suspend") },
  { MODKEY,                       XK_F5,               spawn,          CMD("xbacklight", "-8") },
  { MODKEY,                       XK_F6,               spawn,          CMD("xbacklight", "+8") },
  { MODKEY,                       XK_F1,               spawn,          CMD("pamixer", "-t") },
  { MODKEY,                       XK_F2,               spawn,          CMD("pamixer", "-d", "10") },
  { MODKEY,                       XK_F3,               spawn,          CMD("pamixer", "-i", "10") },
  { 0,                            XF86XK_AudioMicMute, spawn,          CMD("pavucontrol-qt", "-t", "4") },
  { MODKEY|ControlMask,           XK_l,                spawn,          SHCMD("~/.dwm/lock.sh") },
  { MODKEY,                       XK_b,                togglebar,      {0} },
  { MODKEY,                       XK_j,                focusstack,     {.i = +1 } },
  { MODKEY,                       XK_k,                focusstack,     {.i = -1 } },
  { MODKEY,                       XK_comma,            incnmaster,     {.i = +1 } },
  { MODKEY,                       XK_period,           incnmaster,     {.i = -1 } },
  { MODKEY,                       XK_h,                setmfact,       {.f = -0.05} },
  { MODKEY,                       XK_l,                setmfact,       {.f = +0.05} },
  { MODKEY|ShiftMask,             XK_space,            setmfact,       {.f = 1 + MFACT} },
  { MODKEY,                       XK_space,            tagmon,         {.i = +1} },
  { MODKEY,                       XK_Return,           zoom,           {0} },
  { MODKEY,                       XK_Tab,              view,           {0} },
  { MODKEY|ShiftMask,             XK_c,                killclient,     {0} },
  { MODKEY,                       XK_F4,               killclient,     {0} },
  { MODKEY,                       XK_m,                setlayout,      {0} },
  { MODKEY,                       XK_t,                togglefloating, {0} },
  { MODKEY,                       XK_0,                view,           {.ui = ~0 } },
  { MODKEY|ShiftMask,             XK_0,                tag,            {.ui = ~0 } },
  { MODKEY|ControlMask,           XK_Down,             moveresize,     {.v = (const int[]){0,25,0,0}} },
  { MODKEY|ControlMask,           XK_Up,               moveresize,     {.v = (const int[]){0,-25,0,0}} },
  { MODKEY|ControlMask,           XK_Right,            moveresize,     {.v = (const int[]){25,0,0,0}} },
  { MODKEY|ControlMask,           XK_Left,             moveresize,     {.v = (const int[]){-25,0,0,0}} },
  { MODKEY|ShiftMask,             XK_Down,             moveresize,     {.v = (const int[]){0,0,0,25}} },
  { MODKEY|ShiftMask,             XK_Up,               moveresize,     {.v = (const int[]){0,0,0,-25}} },
  { MODKEY|ShiftMask,             XK_Right,            moveresize,     {.v = (const int[]){0,0,25,0}} },
  { MODKEY|ShiftMask,             XK_Left,             moveresize,     {.v = (const int[]){0,0,-25,0}} },
  TAGKEYS(                        XK_1,                                0)
  TAGKEYS(                        XK_2,                                1)
  TAGKEYS(                        XK_3,                                2)
  TAGKEYS(                        XK_4,                                3)
  TAGKEYS(                        XK_5,                                4)
  TAGKEYS(                        XK_6,                                5)
  TAGKEYS(                        XK_7,                                6)
  TAGKEYS(                        XK_8,                                7)
  TAGKEYS(                        XK_9,                                8)
  { MODKEY|ShiftMask,             XK_q,                quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
  /* click                event mask      button          function        argument */
  { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
  { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[1]} },
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

