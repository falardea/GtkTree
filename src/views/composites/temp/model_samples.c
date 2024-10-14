/*
 * Created by french on 3/6/24.
 *
 * Heavily influenced by the GTK 3 TreeView tutorial:
 * https://docs.gtk.org/gtk3/treeview-tutorial.html
*/
#include <math.h>
#include "model_samples.h"
#include "../../../utils/logging.h"

GtkListStore *sampleCalcTable = NULL;

GtkTreeModel *build_samples_model(void)

{
   sampleCalcTable = gtk_list_store_new(NUM_SAMPLES_COLUMNS,
                                               G_TYPE_STRING,
                                               G_TYPE_FLOAT, G_TYPE_FLOAT, G_TYPE_FLOAT, G_TYPE_FLOAT,
                                               G_TYPE_DOUBLE, G_TYPE_DOUBLE);
   GtkTreeIter insertCursor;
   gtk_list_store_append(sampleCalcTable, &insertCursor);
   gtk_list_store_set(sampleCalcTable, &insertCursor,
                      COL_TIMESTAMP, "2023-01-23T12:34:56",
                      COL_MEASUREMENT_1, 1.0, COL_MEASUREMENT_2, 1.0, COL_MEASUREMENT_3, 1.0, COL_MEASUREMENT_4, 1.0,
                      COL_CALCULATED_A, 0.0, COL_CALCULATED_B, 0.0, -1);
   gtk_list_store_append(sampleCalcTable, &insertCursor);
   gtk_list_store_set(sampleCalcTable, &insertCursor,
                      COL_TIMESTAMP, "2023-02-28T23:45:07",
                      COL_MEASUREMENT_1, NAN, COL_MEASUREMENT_2, 1.2, COL_MEASUREMENT_3, 1.3, COL_MEASUREMENT_4, 1.4,
                      COL_CALCULATED_A, 0.0, COL_CALCULATED_B, 0.0, -1);
   gtk_list_store_append(sampleCalcTable, &insertCursor);
   gtk_list_store_set(sampleCalcTable, &insertCursor,
                      COL_TIMESTAMP, "2023-03-04T04:56:08",
                      COL_MEASUREMENT_1, 1.2, COL_MEASUREMENT_2, 1.2, COL_MEASUREMENT_3, 1.2, COL_MEASUREMENT_4, 1.2,
                      COL_CALCULATED_A, 0.0, COL_CALCULATED_B, 0.0, -1);
   gtk_list_store_append(sampleCalcTable, &insertCursor);
   gtk_list_store_set(sampleCalcTable, &insertCursor,
                      COL_TIMESTAMP, "2023-04-05T05:07:09",
                      COL_MEASUREMENT_1, 1.3, COL_MEASUREMENT_2, 1.3, COL_MEASUREMENT_3, 1.3, COL_MEASUREMENT_4, 1.3,
                      COL_CALCULATED_A, 0.0, COL_CALCULATED_B, 0.0, -1);
   gtk_list_store_append(sampleCalcTable, &insertCursor);
   gtk_list_store_set(sampleCalcTable, &insertCursor,
                      COL_TIMESTAMP, "2023-05-06T06:08:10",
                      COL_MEASUREMENT_1, 1.4, COL_MEASUREMENT_2, 1.4, COL_MEASUREMENT_3, 1.4, COL_MEASUREMENT_4, 1.4,
                      COL_CALCULATED_A, 0.0, COL_CALCULATED_B, 0.0, -1);
   logging_llprintf(LOGLEVEL_DEBUG, "%s", __func__ );
   return GTK_TREE_MODEL(sampleCalcTable);
}

void create_new_sample(SamplesRow_T *fromSample)
{
   GtkTreeIter rowCursor;
   gtk_list_store_append(sampleCalcTable, &rowCursor);

   if (fromSample) {
      gtk_list_store_set(sampleCalcTable,
                         &rowCursor,
                         COL_TIMESTAMP,      fromSample->timestampStr,
                         COL_MEASUREMENT_1,  fromSample->measurement1,
                         COL_MEASUREMENT_2,  fromSample->measurement2,
                         COL_MEASUREMENT_3,  fromSample->measurement3,
                         COL_MEASUREMENT_4,  fromSample->measurement4,
                         COL_CALCULATED_A,   fromSample->calculationA,
                         COL_CALCULATED_B,   fromSample->calculationB,
                         -1);
   } else {
      gtk_list_store_set(sampleCalcTable,
                         &rowCursor,
                         COL_TIMESTAMP,      "2021-07-06T06:08:10",
                         COL_MEASUREMENT_1,  NAN,
                         COL_MEASUREMENT_2,  NAN,
                         COL_MEASUREMENT_3,  NAN,
                         COL_MEASUREMENT_4,  NAN,
                         COL_CALCULATED_A,   NAN,
                         COL_CALCULATED_B,   NAN,
                         -1);
   }
}

void get_selected_sample(GtkTreeIter *selected_row, SamplesRow_T *snapshot)
{
   gchararray timestamp;
   gtk_tree_model_get(GTK_TREE_MODEL(sampleCalcTable), selected_row,
                      COL_TIMESTAMP, &timestamp,
                      COL_MEASUREMENT_1, &snapshot->measurement1,
                      COL_MEASUREMENT_2, &snapshot->measurement2,
                      COL_MEASUREMENT_3, &snapshot->measurement3,
                      COL_MEASUREMENT_4, &snapshot->measurement4,
                      COL_CALCULATED_A, &snapshot->calculationA,
                      COL_CALCULATED_B, &snapshot->calculationB,
                      -1);
   strcpy(snapshot->timestampStr, timestamp);
   g_free(timestamp);
}

GtkTreeModel *get_samples_reference(void)
{
   if (sampleCalcTable != NULL)
   {
      return GTK_TREE_MODEL(sampleCalcTable);
   }
   else
   {
      return build_samples_model();
   }
}