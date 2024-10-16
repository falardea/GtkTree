/**
 */
#include "setup_menu_line.h"
#include "utils/logging.h"


#define BLUE_FORMAT_STR(x)               "<span foreground='#0228b1' size='xx-large'>" x "</span>"
#define BLUE_BULLET_FORMAT_STR           BLUE_FORMAT_STR(" \u2022")  // Note the intentional space for alignment
#define BLUE_SELECTED_BULLET_FORMAT_STR  BLUE_FORMAT_STR("\u25ba")

//Setup names of icons from Default Icon Set
const char *StatusIconPath[StepStatus_NbrOfItems] =
      {
            "",                          //StepStatus_NotComplete
            "system-run-symbolic",       //StepStatus_Executing - Don't know if this is actually needed based upon step state needed
            "object-select-symbolic",    //StepStatus_Complete
            "action-unavailable-symbolic" //StepStatus_Skipped
      };

struct _SetupMenuLine
{
   GtkBox      parent;
   gchar       *MenuLineDesc;
   GtkWidget *bulletLabel;
   GtkWidget *descriptionLabel;
   GtkWidget *startButton;
   GtkWidget *skipButton;
   GtkWidget *statusIcon;
   MenuStepStatus_T itemStatus;
   app_widget_ref_struct *app_wdgts_ref;
   void (*startButtonCallback)(GtkButton *button, gpointer user_data);
   void (*skipButtonCallback)(GtkButton *button, gpointer user_data);
};

G_DEFINE_TYPE(SetupMenuLine, setup_menu_line, GTK_TYPE_BOX)

static void setup_menu_line_finalize( GObject *self );

void on_template_btn_start_clicked(GtkButton *button, gpointer user_data)
{
   SetupMenuLine *sml = (SetupMenuLine *)user_data;
   logging_llprintf(LOGLEVEL_DEBUG, "%s", __func__);
   if(sml->startButtonCallback != NULL)
   {
      (* sml->startButtonCallback)(button, sml->app_wdgts_ref);
   }
}

void on_template_btn_skip_clicked(GtkButton *button, gpointer user_data)
{
   SetupMenuLine *sml = (SetupMenuLine *)user_data;
   logging_llprintf(LOGLEVEL_DEBUG, "%s", __func__);
   if(sml->skipButtonCallback != NULL)
   {
      (* sml->skipButtonCallback)(button, sml->app_wdgts_ref);
   }
}

static void setup_menu_line_class_init(SetupMenuLineClass *klass)
{
   GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
   GtkWidgetClass *widget_class = (GtkWidgetClass *) klass;

   logging_llprintf(LOGLEVEL_DEBUG, "%s", __func__);

   gobject_class->finalize = setup_menu_line_finalize;

   gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(klass), "/resource_path/resources/setup_menu_line.glade");
   gtk_widget_class_bind_template_child(widget_class, SetupMenuLine, bulletLabel);
   gtk_widget_class_bind_template_child(widget_class, SetupMenuLine, descriptionLabel);
   gtk_widget_class_bind_template_child(widget_class, SetupMenuLine, startButton);
   gtk_widget_class_bind_template_child(widget_class, SetupMenuLine, skipButton);
   gtk_widget_class_bind_template_child(widget_class, SetupMenuLine, statusIcon);
   gtk_widget_class_bind_template_callback_full(widget_class, "on_template_btn_start_clicked", (GCallback)on_template_btn_start_clicked);
   gtk_widget_class_bind_template_callback_full(widget_class, "on_template_btn_skip_clicked", (GCallback)on_template_btn_skip_clicked);
   logging_llprintf(LOGLEVEL_DEBUG, "%s", __func__);
}

static void setup_menu_line_init(SetupMenuLine *self)
{
   logging_llprintf(LOGLEVEL_DEBUG, "%s", __func__);
   gtk_widget_init_template(GTK_WIDGET(self));
   logging_llprintf(LOGLEVEL_DEBUG, "%s", __func__);
}

GtkWidget *setup_menu_line_new(const gchar *menu_line_descript,
                               SetupMenuLineCallback_T fStartButtonCallback,
                               SetupMenuLineCallback_T fSkipButtonCallback,
                               app_widget_ref_struct *wdgts)
{
   SetupMenuLine *sml;

   logging_llprintf(LOGLEVEL_DEBUG, "%s", __func__);

   sml = g_object_new(SETUP_MENU_TYPE_LINE, NULL);

   if (menu_line_descript != NULL)
   {
      setup_menu_line_set_MenuLineDesc(sml, menu_line_descript);
   }

   sml->startButtonCallback = fStartButtonCallback;
   sml->skipButtonCallback = fSkipButtonCallback;
   sml->app_wdgts_ref = wdgts;

   return GTK_WIDGET(sml);
}

gchar *setup_menu_line_get_MenuLineDesc (SetupMenuLine *self)
{
   g_return_val_if_fail(self != NULL, NULL);
   g_return_val_if_fail(SETUP_MENU_IS_LINE(self), NULL);

   return g_strdup(self->MenuLineDesc);
}
void setup_menu_line_set_MenuLineDesc (SetupMenuLine *self, const char* menu_line_descript)
{
   g_return_if_fail(self != NULL);
   g_return_if_fail(SETUP_MENU_IS_LINE(self));
   g_return_if_fail(menu_line_descript != NULL);

   logging_llprintf(LOGLEVEL_DEBUG, "%s", __func__);

   if(self->MenuLineDesc != NULL)
   {
      g_free(self->MenuLineDesc);
   }
   self->MenuLineDesc = g_strdup(menu_line_descript);
   gtk_label_set_markup(GTK_LABEL(self->descriptionLabel), self->MenuLineDesc);

   gtk_label_set_label(GTK_LABEL(self->bulletLabel), BLUE_BULLET_FORMAT_STR);
}

static void setup_menu_line_finalize( GObject *self )
{
   g_return_if_fail(self != NULL);
   g_return_if_fail(SETUP_MENU_IS_LINE(self));

   logging_llprintf(LOGLEVEL_DEBUG, "%s", __func__);

   G_OBJECT_CLASS (setup_menu_line_parent_class)->finalize (self);
}
