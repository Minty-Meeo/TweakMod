#ifndef OUTPUT_H
#define OUTPUT_H

void toWavefrontObj( shape& mainShape, char* filename );
void toDolphinModel( shape& mainShape, char* filename );
void toShape( shape& mainShape, char* filename );
void exportINI( shape& mainShape, char* filename );
void exportBTI( shape& mainShape, char* filename );

#endif /* OUTPUT_H */
