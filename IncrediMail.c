#include "compat/stdint.h"

#if defined(__has_include)
  /* Prefer proto/ headers when available (AmigaOS4 style), otherwise fall back */
  #if __has_include(<proto/exec.h>)
    #include <proto/exec.h>
    #include <proto/intuition.h>
    #include <proto/muimaster.h>
    #include <proto/dos.h>
    #include <libraries/mui.h>
  #elif __has_include(<exec/exec.h>)
    #include <exec/exec.h>
    #include <intuition/intuition.h>
    #include <dos/dos.h>
    #include <libraries/mui.h>
  #else
    #error "Required AmigaOS headers not found: <proto/exec.h> or <exec/exec.h>"
  #endif
#else
  /* Fallback for compilers without __has_include - prefer non-proto headers */
  #include <exec/exec.h>
  #include <intuition/intuition.h>
  #include <dos/dos.h>
  #include <libraries/mui.h>
#endif

/* Global Bases */
struct Library *MUIMasterBase;
struct IntuitionBase *IntuitionBase;

int main(void)
{
    Object *app, *window;

    // Open libraries
    IntuitionBase = (struct IntuitionBase *)OpenLibrary("intuition.library", 37);
    MUIMasterBase = OpenLibrary("muimaster.library", 19); // 19 is MUI 3.8+, 20 is MUI 5.0

    if (!MUIMasterBase || !IntuitionBase)
    {
        if (IntuitionBase) CloseLibrary((struct Library *)IntuitionBase);
        return 20;
    }

    app = ApplicationObject,
        MUIA_Application_Title, "IncrediMail Apollo",
        MUIA_Application_Version, "$VER: IncrediMail 0.1 (2026-01-17)", // Datum van vandaag
        MUIA_Application_Copyright, "© 2026 Paul Bertelink",
        MUIA_Application_Author, "Paul Bertelink",
        
        SubWindow, window = WindowObject,
            MUIA_Window_Title, "IncrediMail 2026",
            MUIA_Window_ID, MAKE_ID('I','M','A','I'),
            WindowContents, VGroup,
                Child, TextObject,
                    MUIA_Text_Contents, "\33cWelkom bij IncrediMail voor ApolloOS!", // \33c centreert tekst
                End,
                Child, SimpleButton("Nieuwe mail ophalen"),
            End,
        End,
    End;

    if (app)
    {
        // Zet de window open
        set(window, MUIA_Window_Open, TRUE);
        
        // Start de event loop
        DoMethod(app, MUIM_Application_Execute);
        
        // Ruim alles netjes op
        MUI_DisposeObject(app);
    }

    CloseLibrary(MUIMasterBase);
    CloseLibrary((struct Library *)IntuitionBase);

    return 0;
}
