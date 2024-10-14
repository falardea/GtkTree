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
   gtk_list_store_set(combo_sample, &iter, 0, "Item 1", 1, 12, -1); // , 1, 23, 2, "4", -1);
   gtk_list_store_append(combo_sample, &iter);
   gtk_list_store_set(combo_sample, &iter, 0, "Item 2",  1, 23, -1); // , 1, 34, 2, "5", -1);
   gtk_list_store_append(combo_sample, &iter);
   gtk_list_store_set(combo_sample, &iter, 0, "Item 3",  1, 34, -1); // , 1, 45, 2, "6", -1);
   gtk_list_store_append(combo_sample, &iter);
   gtk_list_store_set(combo_sample, &iter, 0, "Item 4",  1, 45, -1); // , 1, 56, 2, "7", -1);

   gtk_combo_box_set_active(GTK_COMBO_BOX(wdgts->w_basic_items_combo), 0);
   gtk_combo_box_set_id_column(GTK_COMBO_BOX(wdgts->w_basic_items_combo), 0);

   /////////////////////////////////////////////////////////////////////////////
   g_object_unref(combo_sample);

}
