/**
 * @brief Application entry point
 */
#include <gtk/gtk.h>
#include <stdlib.h>
#include "version.h"
#include "interfaces/app_interface.h"
#include "utils/logging.h"

void run_console_context(void);

int main(int argc, char **argv) {
   printf("ver.%d.%d.%d\n", project_VERSION_MAJOR, project_VERSION_MINOR, project_VERSION_PATCH);

   app_init(argc, argv);

   if (get_app_state() == APP_STATE_SUCCESS)
   {
      if (!get_app_run_console_only())
      {
         logging_llprintf(LOGLEVEL_INFO, "application initialized, starting UI");
         gtk_main();
         logging_llprintf(LOGLEVEL_INFO, "UI closed, shutting down");
      } else {
         run_console_context();
      }
   }
   else
   {
      logging_llprintf(LOGLEVEL_ERROR, "application initialization failed, attempting a graceful shutdown");
      // Graceful shutdown
   }

   app_finalize();

   return get_app_state();
}

#define APPLICATION_ROOT               "Root"
#define APPLICATION_DETAILS            "Details"
#define APPLICATION_NAME               "Application Name"
#define APPLICATION_AUTHOR             "Owner"
#define APPLICATION_URL                "Url"
#define APPLICATION_VERSION_MMP       "Version"

void run_console_context(void)
{
   logging_llprintf(LOGLEVEL_INFO, "%s", __func__);

   GHashTable *app_data = g_hash_table_new(g_str_hash, g_str_equal);
   GHashTable *app_details_hash = g_hash_table_new(g_str_hash, g_str_equal);
   GList      *app_version_trio = NULL;
   g_hash_table_insert(app_data, APPLICATION_ROOT, "Application Root Storage Object");
   g_hash_table_insert(app_details_hash, APPLICATION_NAME, project_PROJECT_NAME);
   g_hash_table_insert(app_details_hash, APPLICATION_AUTHOR, project_AUTHOR);

   // Major, Minor, Patch
   app_version_trio = g_list_append(app_version_trio, GINT_TO_POINTER(project_VERSION_MAJOR));
   app_version_trio = g_list_append(app_version_trio, GINT_TO_POINTER(project_VERSION_MINOR));
   app_version_trio = g_list_append(app_version_trio, GINT_TO_POINTER(project_VERSION_PATCH));

   g_hash_table_insert(app_details_hash, APPLICATION_VERSION_MMP, app_version_trio);
   g_hash_table_insert(app_details_hash, APPLICATION_URL, project_URL);

   g_hash_table_insert(app_data, APPLICATION_DETAILS, app_details_hash);

   gchar *root_value = g_hash_table_lookup(app_data, APPLICATION_ROOT);

   if (root_value != NULL)
   {
      g_print("%s: %s\n", __func__, root_value);

      GHashTable *details = g_hash_table_lookup(app_data, APPLICATION_DETAILS);

      g_print("\t - %s=%s\n", APPLICATION_NAME, (char*)g_hash_table_lookup(details, APPLICATION_NAME));
      g_print("\t - %s=%s\n", APPLICATION_AUTHOR, (char*)g_hash_table_lookup(details, APPLICATION_AUTHOR));
      g_print("\t - %s=%s\n", APPLICATION_URL, (char*)g_hash_table_lookup(details, APPLICATION_URL));
      g_print("\t - %s:v%d.%d.%d\n", "Version",
              GPOINTER_TO_INT(g_list_nth_data ((GList*)g_hash_table_lookup(details, APPLICATION_VERSION_MMP), 0)),
              GPOINTER_TO_INT(g_list_nth_data ((GList*)g_hash_table_lookup(details, APPLICATION_VERSION_MMP), 1)),
              GPOINTER_TO_INT(g_list_nth_data ((GList*)g_hash_table_lookup(details, APPLICATION_VERSION_MMP), 2)));
   }
   else
   {
      g_print("%s: %s\n", __func__, "g_hash_table_lookup failed");
   }

   g_list_free(app_version_trio);
   g_hash_table_unref(app_details_hash);
   g_hash_table_unref(app_data);
}