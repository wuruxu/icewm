#include "config.h"
#ifndef NO_CONFIGURE
#define CFGDESC
#include "ykey.h"
#include "sysdep.h"

void addWorkspace(const char *, const char *, bool) {}
void setLook(const char *, const char *, bool) {}
void addBgImage(const char *, const char *, bool) {}

//#include "bindkey.h"
//#include "default.h"
#define CFGDEF
#define GENPREF
#include "yprefs.h"
#include "bindkey.h"
#include "default.h"
#include "themable.h"
#include "icewmbg_prefs.h"

void show(cfoption *options) {
    for (unsigned int i = 0; options[i].type != cfoption::CF_NONE; i++) {
        if (options[i].description)
            printf("#  %s\n", options[i].description);

        switch (options[i].type) {
        case cfoption::CF_BOOL:
            printf("# %s=%d # 0/1\n",
                   options[i].name, (*options[i].v.bool_value) ? 1 : 0);
            break;
        case cfoption::CF_INT:
            printf("# %s=%d # [%d-%d]\n",
                   options[i].name, *options[i].v.i.int_value,
                   options[i].v.i.min, options[i].v.i.max);
            break;
        case cfoption::CF_STR:
            if (options[i].v.s.string_value) {
                printf("# %s=\"%s\"\n",
                       options[i].name,
                       (*options[i].v.s.string_value) ? (*options[i].v.s.string_value) : "");
            }
            break;
#ifndef NO_KEYBIND
        case cfoption::CF_KEY:
            {
                WMKey *key = options[i].v.k.key_value;

                printf("# %s=\"%s\"\n", options[i].name, key->name);
            }
            break;
#endif
        case cfoption::CF_NONE:
            break;
        }
        if (options[i].description)
            puts("");
    }
}
#endif

int main() {
#ifndef NO_CONFIGURE
    printf("# preferences(%s) - generated by genpref\n\n", VERSION);
    printf("# This file should be copied to /etc/icewm/ or $HOME/.icewm/ directory\n");
    printf("# NOTE: All settings are commented out by default, be sure to\n"
           "#       uncomment them if you change them!\n\n");

    show(icewm_preferences);

    printf("# -----------------------------------------------------------\n"
           "# Themable preferences. Themes will override these.\n"
           "# To override the themes, place them in ~/.icewm/prefoverride\n"
           "# -----------------------------------------------------------\n\n");
    
    show(icewm_themable_preferences);

    // special case, for now
    puts("WorkspaceNames=\"Dev\", \"Web\", \"Work\"");

    puts("\n#\n# icewmbg preferences\n#");
    puts("# IMPORTANT: You MUST run icewmbg (probably before icewm)\n"
         "#            to set the background!\n#\n");
    show(icewmbg_prefs);
#endif
}
