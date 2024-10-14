/**
 * @brief The implementation
 */
#include <gtk/gtk.h>
#include "app_globals.h"
#include "ui_builder.h"
#include "utils/logging.h"
#include "views/composites/temp/view_samples.h"
#include "views/composites/temp/model_samples.h"

#define GET_WIDGET(wdgt)   appWidgetsT->w_##wdgt = GTK_WIDGET(gtk_builder_get_object(builder, #wdgt))
#define GET_OBJECT(wdgt)   appWidgetsT->g_##wdgt = G_OBJECT(gtk_builder_get_object(builder, #wdgt))

#define BIND_SENSITIVITY_TO_ACTIVE(wdgt, wdgt_sensitive_to)    \
            g_object_bind_property(appWidgetsT->w_##wdgt_sensitive_to, "active", \
            appWidgetsT->w_##wdgt , "sensitive", \
            G_BINDING_DEFAULT);

#define GET_WDGT_AND_BIND_SENS2ACTIVE(wdgt, wdgt_sensitive_to) \
            appWidgetsT->w_##wdgt = GTK_WIDGET(gtk_builder_get_object(builder, #wdgt)); \
            g_object_bind_property( appWidgetsT->w_##wdgt_sensitive_to, "active", \
            appWidgetsT->w_##wdgt , "sensitive", \
            G_BINDING_DEFAULT);


app_widget_ref_struct *app_builder(void) {
   GtkBuilder *builder;

   app_widget_ref_struct *appWidgetsT = g_slice_new(app_widget_ref_struct);

   builder = gtk_builder_new();

   if (gtk_builder_add_from_resource(builder, "/resource_path/resources/gtk_tree.glade", NULL) == 0) {
      logging_llprintf(LOGLEVEL_ERROR, "failed to load glade resource");
      return NULL;
   }

   GET_WIDGET(msg_out_textview);
   GET_WIDGET(say_something_entry);
   GET_WIDGET(do_something_button);
   GET_WIDGET(home_page_overlay);

   GET_WIDGET(basic_items_combo);
   GET_WIDGET(timestamp_selection_combobox);

   GET_WIDGET(brand_logo);

   GET_WIDGET(trvwSamplesTable);
   GET_OBJECT(trslctnSelectedSample);

   GET_WIDGET(tbtnEditSelection);
   GET_WIDGET(tbtnCreateRow);
   GET_WIDGET(tbtnDeleteRow);

   GET_WIDGET(ppvrAreYouSure);
   GET_WIDGET(lblPopoverAreYouSureMsg);
   GET_WIDGET(btnAreYouSureConfirm);
   GET_WIDGET(btnAreYouSureCancel);

   // GET_WIDGET(editSampleDateTime);
   GET_WDGT_AND_BIND_SENS2ACTIVE(editSampleDateTime, tbtnEditSelection);
   GET_WDGT_AND_BIND_SENS2ACTIVE(entrySampleHour, tbtnEditSelection);
   GET_WDGT_AND_BIND_SENS2ACTIVE(entrySampleMinute, tbtnEditSelection);
   GET_WDGT_AND_BIND_SENS2ACTIVE(entryMeasurement1, tbtnEditSelection);
   GET_WDGT_AND_BIND_SENS2ACTIVE(entryMeasurement2, tbtnEditSelection);
   GET_WDGT_AND_BIND_SENS2ACTIVE(entryMeasurement3, tbtnEditSelection);
   GET_WDGT_AND_BIND_SENS2ACTIVE(entryMeasurement4, tbtnEditSelection);

   GET_WDGT_AND_BIND_SENS2ACTIVE(entryCalculationA, tbtnEditSelection);
   GET_WDGT_AND_BIND_SENS2ACTIVE(entryCalculationB, tbtnEditSelection);

   GET_WDGT_AND_BIND_SENS2ACTIVE(btnChangeRow, tbtnEditSelection);
   GET_WDGT_AND_BIND_SENS2ACTIVE(btnCancelRowChange, tbtnEditSelection);

   GET_WDGT_AND_BIND_SENS2ACTIVE(lblSampleDate, tbtnEditSelection);

   // Datepicker
   GET_WIDGET(ppvrDatepicker);
   GET_WIDGET(popCalendar);
   GET_WIDGET(popDone);
   GET_WIDGET(popCancel);

   // set up the table column definitions
   build_samples_view(appWidgetsT->w_trvwSamplesTable);
   // build, and possibly populate from <...>, a model of the data to bind to the table as its "TreeModel"
   gtk_tree_view_set_model(GTK_TREE_VIEW(appWidgetsT->w_trvwSamplesTable), get_samples_reference());
   gtk_combo_box_set_model(GTK_COMBO_BOX(appWidgetsT->w_timestamp_selection_combobox), GTK_TREE_MODEL(get_samples_reference()));

   // GtkListStore *combo_sample = gtk_list_store_new(3, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING);
   GtkListStore *combo_sample = gtk_list_store_new(1, G_TYPE_STRING);
   gtk_combo_box_set_model(GTK_COMBO_BOX(appWidgetsT->w_basic_items_combo), GTK_TREE_MODEL(combo_sample));

   GtkTreeIter iter;
   gtk_list_store_append(combo_sample, &iter);
   gtk_list_store_set(combo_sample, &iter, 0, "Item 1", -1); // , 1, 23, 2, "4", -1);
   gtk_list_store_append(combo_sample, &iter);
   gtk_list_store_set(combo_sample, &iter, 0, "Item 2", -1); // , 1, 34, 2, "5", -1);
   gtk_list_store_append(combo_sample, &iter);
   gtk_list_store_set(combo_sample, &iter, 0, "Item 3", -1); // , 1, 45, 2, "6", -1);
   gtk_list_store_append(combo_sample, &iter);
   gtk_list_store_set(combo_sample, &iter, 0, "Item 4", -1); // , 1, 56, 2, "7", -1);

   GtkCellRenderer *combocell = gtk_cell_renderer_text_new ();
   gtk_cell_layout_pack_start( GTK_CELL_LAYOUT(appWidgetsT->w_basic_items_combo), combocell, TRUE );
   gtk_cell_layout_set_attributes( GTK_CELL_LAYOUT(appWidgetsT->w_basic_items_combo), combocell, "text", 0, NULL );

   gtk_combo_box_set_active(GTK_COMBO_BOX(appWidgetsT->w_basic_items_combo), 0);
   gtk_combo_box_set_active(GTK_COMBO_BOX(appWidgetsT->w_timestamp_selection_combobox), 0);
   gtk_combo_box_set_id_column(GTK_COMBO_BOX(appWidgetsT->w_basic_items_combo), 0);

   gtk_builder_connect_signals(builder, appWidgetsT);

   g_object_unref(builder);
   g_object_unref(combo_sample);
   return appWidgetsT;
}
