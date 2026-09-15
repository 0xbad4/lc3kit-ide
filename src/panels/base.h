#pragma once

#include "utils/common.h"
#include "utils/logger.h"
#include "utils/settings.h"
#include "themes/proxy.h"
#include "themes/tman.h"


namespace lc3kit::ide
{
    class BaseController {
        public:
            virtual QString name() = 0;
            void on_halted() {}
    };
} // namespace lc3kit::ide
