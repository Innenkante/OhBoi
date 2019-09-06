#include "stdafx.h"
#include "Globals.h"


JRuntime* Globals::JavascriptRuntime = new JRuntime();
TypeParser* Globals::ValueParser = new TypeParser();
CollectionParser* Globals::ArrayParser = new CollectionParser();
