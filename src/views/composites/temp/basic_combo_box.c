/**
 * @file basic_combo_box.c
 *
 * @copyright
 * COPYRIGHT 2024
 * DEKA RESEARCH AND DEVELOPMENT CORPORATION
 *
 * Contains confidential and proprietary information which
 * may not be copied, disclosed or used by others except as expressly
 * authorized in writing by DEKA Research & Development Corporation.
 *
 * @critical <Minor, Moderate, Major Single-Point, Major Multi-Point>
 * @brief <brief description of the file>
 * @subsystem <subsystem name>
 */
#include <gtk/gtk.h>
#include "basic_combo_box.h"
#include "utils/logging.h"

enum {
   BASIC_COMBO_SELECTION_0,
   BASIC_COMBO_SELECTION_1,
   BASIC_COMBO_SELECTION_2,
   BASIC_COMBO_SELECTION_3,
   BASIC_COMBO_N_SELECTIONS
};

typedef struct BasicCombo_I2Str
{
   int            index;
   const gchar*   display_text;
} BasicCombo_I2Str;

BasicCombo_I2Str bcb_items[BASIC_COMBO_N_SELECTIONS] =
      {
            {BASIC_COMBO_SELECTION_0, "Samples Table"},
            {BASIC_COMBO_SELECTION_1, "Tree Explorer"},
            {BASIC_COMBO_SELECTION_2, "Empty"},
            {BASIC_COMBO_SELECTION_3, "Empty"},
      };

void build_basic_combo_box(app_widget_ref_struct *wdgts)
{
   /////////////////////////////////////////////////////////////////////////////
   // GtkListStore *combo_sample = gtk_list_store_new(3, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING);
   GtkListStore *combo_sample = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_INT);
   GtkCellRenderer *combocell = gtk_cell_renderer_text_new ();
   GtkCellRenderer *combocell2 = gtk_cell_renderer_text_new ();

   gtk_combo_box_set_model(GTK_COMBO_BOX(wdgts->w_basic_items_combo), GTK_TREE_MODEL(combo_sample));
   gtk_cell_layout_pack_start( GTK_CELL_LAYOUT(wdgts->w_basic_items_combo), combocell, TRUE );
   gtk_cell_layout_pack_start( GTK_CELL_LAYOUT(wdgts->w_basic_items_combo), combocell2, TRUE );
   gtk_cell_layout_set_attributes( GTK_CELL_LAYOUT(wdgts->w_basic_items_combo), combocell, "text", 0, NULL );
   gtk_cell_layout_set_attributes( GTK_CELL_LAYOUT(wdgts->w_basic_items_combo), combocell2, "text", 1, NULL );

   GtkTreeIter iter;
   gtk_list_store_append(combo_sample, &iter);
   gtk_list_store_set(combo_sample, &iter, 0, bcb_items[BASIC_COMBO_SELECTION_0].display_text, 1, 0, -1); // , 1, 23, 2, "4", -1);
   gtk_list_store_append(combo_sample, &iter);
   gtk_list_store_set(combo_sample, &iter, 0, bcb_items[BASIC_COMBO_SELECTION_1].display_text,  1, 1, -1); // , 1, 34, 2, "5", -1);
   gtk_list_store_append(combo_sample, &iter);
   gtk_list_store_set(combo_sample, &iter, 0, bcb_items[BASIC_COMBO_SELECTION_2].display_text,  1, 2, -1); // , 1, 45, 2, "6", -1);
   gtk_list_store_append(combo_sample, &iter);
   gtk_list_store_set(combo_sample, &iter, 0, bcb_items[BASIC_COMBO_SELECTION_3].display_text,  1, 3, -1); // , 1, 56, 2, "7", -1);

   gtk_combo_box_set_active(GTK_COMBO_BOX(wdgts->w_basic_items_combo), 0);
   gtk_combo_box_set_id_column(GTK_COMBO_BOX(wdgts->w_basic_items_combo), 0);

   /////////////////////////////////////////////////////////////////////////////
   g_object_unref(combo_sample);

}


void on_basic_items_combo_changed(__attribute__((unused)) GtkComboBox *comboBox, __attribute__((unused)) gpointer user_data)
{
   app_widget_ref_struct *wdgts = (app_widget_ref_struct *) user_data;
   GtkTreeIter tIter;
   GValue current_selection = {0};

   if (gtk_combo_box_get_active_iter(comboBox, &tIter))
   {
      GtkTreeModel *model = gtk_combo_box_get_model(comboBox);
      gtk_tree_model_get_value(model, &tIter, 0, &current_selection);

      int found_index = -1;
      for (int i=0; i< BASIC_COMBO_N_SELECTIONS; i++)
      {
         if (strcmp(g_value_get_string(&current_selection), bcb_items[i].display_text) == 0)
         {
            found_index = i;
         }
      }

      if (found_index >= 0)
      {
         logging_llprintf(LOGLEVEL_DEBUG, "%s %s, page index=%d", "Should be going to", bcb_items[found_index].display_text,
                          bcb_items[found_index].index);
         gtk_stack_set_visible_child(GTK_STACK(wdgts->w_model_viewers),
                                     gtk_stack_get_child_by_name(GTK_STACK(wdgts->w_model_viewers), bcb_items[found_index].display_text));
      }

   }
}