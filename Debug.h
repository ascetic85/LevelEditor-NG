#ifndef DEBUG_H
#define DEBUG_H

#include <QDebug>

#define Debug qDebug

#define SAFE_DELETE(x) if (x) delete x;

#define SAFE_FREE(x) if (x) free(x);

#endif // DEBUG_H
