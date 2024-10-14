/*
 * Created by french on 3/6/24.
*/
#ifndef MODEL_SAMPLES_H__
#define MODEL_SAMPLES_H__
#include <gtk/gtk.h>

typedef enum {
   COL_TIMESTAMP = 0,
   COL_MEASUREMENT_1,
   COL_MEASUREMENT_2,
   COL_MEASUREMENT_3,
   COL_MEASUREMENT_4,
   COL_CALCULATED_A,
   COL_CALCULATED_B,
   NUM_SAMPLES_COLUMNS
} SAMPLES_COLUMNS_T;

/* This is meant to be effectively a mirror of the ListStore columns, used to carry the retrieved values
 * from gtk_tree_model_get
 * NOTE: it is EXTREMELY important that the sizes of these variables match the size declared for the column
 *       they mirror, or you will get undefined behavior as GTK writes to memory we don't own.
 */
typedef struct {
   float measurement1;
   float measurement2;
   float measurement3;
   float measurement4;
   double calculationA;
   double calculationB;
   gchar timestampStr[sizeof("YYYY-MM-DD HH:mm:ss.sss-12:34Z")];
} SamplesRow_T;

GtkTreeModel *build_samples_model(void);
void create_new_sample(SamplesRow_T *fromSample);
void get_selected_sample(GtkTreeIter *selected_row, SamplesRow_T *snapshot);

GtkTreeModel *get_samples_reference(void);

#endif  /* MODEL_SAMPLES_H__ */
