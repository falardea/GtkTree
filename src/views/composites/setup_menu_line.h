/**
 */
#ifndef SETUP_MENU_LINE_H__
#define SETUP_MENU_LINE_H__
#include "app_globals.h"
G_BEGIN_DECLS

typedef enum
{
   StepStatus_NotComplete,
   StepStatus_Executing,
   StepStatus_Complete,
   StepStatus_Skipped,
   StepStatus_NbrOfItems
} MenuStepStatus_T;

#define SETUP_MENU_TYPE_LINE  (setup_menu_line_get_type())

G_DECLARE_FINAL_TYPE(SetupMenuLine, setup_menu_line, SETUP_MENU, LINE, GtkBox)

typedef void (*SetupMenuLineCallback_T)(GtkButton *button, gpointer user_data);

GtkWidget *setup_menu_line_new(const gchar *menu_line_descript,
                               SetupMenuLineCallback_T fStartButtonCallback,
                               SetupMenuLineCallback_T fSkipButtonCallback,
                               app_widget_ref_struct *wdgts);

gchar *setup_menu_line_get_MenuLineDesc (SetupMenuLine *self);
void setup_menu_line_set_MenuLineDesc (SetupMenuLine *self, const char* menu_line_descript);

G_END_DECLS
#endif  // SETUP_MENU_LINE_H__
