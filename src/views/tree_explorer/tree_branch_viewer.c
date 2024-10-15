/**
 */
#include "app_globals.h"
#include "version.h"
#include "tree_branch_viewer.h"
#include "utils/logging.h"

enum
{
   FIELD_NAME = 0,
   FIELD_VALUE,
   FIELD_EDITABLE,
   N_FIELD_COLS
};

GtkTreeStore *appTreeModel = NULL;

static GtkTreeModel *create_and_build_app_tree_model(void)
{
   appTreeModel = gtk_tree_store_new(N_FIELD_COLS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_BOOLEAN);

   GtkTreeIter iter;
   gtk_tree_store_append(appTreeModel, &iter, NULL);  // create new row and move iterator to it
   gtk_tree_store_set(appTreeModel, &iter, FIELD_NAME, "Application Name", FIELD_VALUE, "GtkTree", FIELD_EDITABLE, FALSE, -1);
   gtk_tree_store_append(appTreeModel, &iter, NULL);
   gtk_tree_store_set(appTreeModel, &iter, FIELD_NAME, "Application Description", FIELD_VALUE, "A sandbox for testing GTK3 TreeModel and TreeView concepts", FIELD_EDITABLE, TRUE, -1);
   gtk_tree_store_append(appTreeModel, &iter, NULL);
   gtk_tree_store_set(appTreeModel, &iter, FIELD_NAME, "Version", FIELD_VALUE, "0.0.1", FIELD_EDITABLE, FALSE, -1);

   return GTK_TREE_MODEL(appTreeModel);
}

void cell_boolean_formatter(__attribute__((unused)) GtkTreeViewColumn   *col,
                           GtkCellRenderer     *renderer,
                           GtkTreeModel        *model,
                           GtkTreeIter         *rowCursor,
                           __attribute__((unused)) gpointer            user_data)
{
   gboolean enabled;
   GdkRGBA redColor = {255.0, 0.0, 0.0, 1.0};
   GdkRGBA greenColor = {0.0, 255.0, 0.0, 1.0};

   gtk_tree_model_get(model, rowCursor, 2, &enabled, -1);

   g_object_set(renderer, "text", enabled ? "enabled":"disabled",
                "cell-background-rgba", enabled ? &greenColor:&redColor, NULL);
}

void create_app_tree_viewer_with_model(app_widget_ref_struct *wdgts)
{
   create_and_build_app_tree_model();
   GtkCellRenderer *t_renderer, *en_renderer;

   t_renderer = gtk_cell_renderer_text_new();
   en_renderer = gtk_cell_renderer_text_new();
   gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(wdgts->w_tree_branch_view), -1,
                                               "Field Name", t_renderer,
                                               "text", FIELD_NAME, NULL);

   g_object_set(G_OBJECT(t_renderer),
                "width-chars", 30,
                "max-width-chars", 30,
                "ellipsize", PANGO_ELLIPSIZE_END, NULL);

   gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(wdgts->w_tree_branch_view),
                                               -1, "Field Value", t_renderer,
                                               "text", FIELD_VALUE,
                                               NULL);
   gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(wdgts->w_tree_branch_view), -1,
                                               "Editable", t_renderer,
                                               "text", FIELD_EDITABLE, NULL);

   gtk_tree_view_insert_column_with_data_func(GTK_TREE_VIEW(wdgts->w_tree_branch_view), -1,
                                              "Enabled", en_renderer,
                                              cell_boolean_formatter, NULL, NULL);

   g_object_set(t_renderer, "cell-background", "white", "cell-background-set", TRUE, NULL);

   gtk_tree_view_set_model(GTK_TREE_VIEW(wdgts->w_tree_branch_view), GTK_TREE_MODEL(appTreeModel));
}

void on_trslctnSelectedTreeBranch_changed(GtkTreeSelection* self, gpointer user_data)
{
//   app_widget_ref_struct *wdgts = (app_widget_ref_struct *)user_data;
   GtkTreeIter treeCursor;
   GtkTreeModel *treeModel;

   if (gtk_tree_selection_get_selected (GTK_TREE_SELECTION(self), &treeModel, &treeCursor))
   {
      logging_llprintf(LOGLEVEL_DEBUG, "%s", __func__);
   }
}
