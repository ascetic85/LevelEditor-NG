#ifndef DEBUG_H
#define DEBUG_H

#include <QDebug>

#define Debug qDebug

#define SAFE_DELETE(x) if (x)  {delete x; x = NULL; }

#define SAFE_FREE(x) if (x) { free(x), x = NULL} ;

#endif // DEBUG_H
