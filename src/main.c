/**
 * @brief Application entry point
 */
#include <gtk/gtk.h>
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

void run_console_context(void)
{
   logging_llprintf(LOGLEVEL_INFO, "%s", __func__);

   GHashTable *app_data = g_hash_table_new(g_str_hash, g_str_equal);
   GHashTable *app_details_hash = g_hash_table_new(g_str_hash, g_str_equal);

   char buf[20];
   snprintf(buf, sizeof(buf), "ver.%d.%d.%d\n", project_VERSION_MAJOR, project_VERSION_MINOR, project_VERSION_PATCH);

   g_hash_table_insert(app_data, "Root", "GtkTree Application");
   g_hash_table_insert(app_details_hash, "Application Name", "GtkTree");
   g_hash_table_insert(app_details_hash, "Author", "my_name_here");
   g_hash_table_insert(app_details_hash, "Version String", buf);
   g_hash_table_insert(app_details_hash, "Version major", GINT_TO_POINTER(project_VERSION_MAJOR));
   g_hash_table_insert(app_details_hash, "Version minor", GINT_TO_POINTER(project_VERSION_MINOR));
   g_hash_table_insert(app_details_hash, "Version patch", GINT_TO_POINTER(project_VERSION_PATCH));
   g_hash_table_insert(app_details_hash, "Description", "A GTK3 application to explore trees as data structures and "
                                                       "as a basic skeleton for application data.");
   g_hash_table_insert(app_data, "Details", app_details_hash);


   gchar *root_value = g_hash_table_lookup(app_data, "Root");

   if (root_value != NULL)
   {
      g_print("%s: %s\n", __func__, root_value);

      GHashTable *details = g_hash_table_lookup(app_data, "Details");

      g_print("\t - %s\n", g_hash_table_lookup(details, "Application Name"));
      g_print("\t - %s\n", g_hash_table_lookup(details, "Author"));
      g_print("\t - %s\n", g_hash_table_lookup(details, "Version String"));
      g_print("\t - %s\n", g_hash_table_lookup(details, "Version major"));
      g_print("\t - %s\n", g_hash_table_lookup(details, "Version minor"));
      g_print("\t - %s\n", g_hash_table_lookup(details, "Version patch"));
      g_print("\t - %s\n", g_hash_table_lookup(details, "Description"));
   }
   else
   {
      g_print("%s: %s\n", __func__, "g_hash_table_lookup failed");
   }

   g_hash_table_unref(app_data);
   g_hash_table_unref(app_details_hash);

}