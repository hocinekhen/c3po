/*
* Copyright 2019-present Open Networking Foundation
* Copyright (c) 2017 Sprint
*
* SPDX-License-Identifier: Apache-2.0
*/

#ifndef __LOGGER_H
#define __LOGGER_H

#include <cstdarg>
#include <stdexcept>
#include <vector>

#include "slogger.h"

//#define SPDLOG_LEVEL_NAMES { "trace", "debug", "info",  "warning", "error", "critical", "off" };
#define SPDLOG_LEVEL_NAMES { "trace", "debug", "info",  "startup", "warn", "error", "off" };

#define SPDLOG_ENABLE_SYSLOG
#include "spdlog/spdlog.h"

class Logger
{
public:

   static void init( const char *app ) { singleton()._init( app ); }
   static void init( const std::string &app ) { init( app.c_str() ); }
   static void cleanup() { singleton()._cleanup(); }
   static void flush() { singleton()._flush(); }
   static std::string serialize() { return singleton()._serialize(); }
   static bool updateLogger(const std::string &loggerName, int value) { return singleton()._updateLogger(loggerName, value); }

   static SLogger &system() { return *singleton().m_system; }
   static SLogger &s6as6d() { return *singleton().m_s6as6d; }
   static SLogger &s6c() { return *singleton().m_s6c; }
   static SLogger &s6t() { return *singleton().m_s6t; }
   static SLogger &stat() { return *singleton().m_stat; }
   static SLogger &audit() { return *singleton().m_audit; }

   static Logger &singleton() { if (!m_singleton) m_singleton = new Logger(); return *m_singleton; }

private:
   static Logger *m_singleton;


   Logger() {}
   ~Logger() {}

   void _init( const char *app );
   void _cleanup();
   void _flush();
   std::string _serialize();
   bool _updateLogger(const std::string &loggerName, int value);

   std::vector<spdlog::sink_ptr> m_sinks;
   std::vector<spdlog::sink_ptr> m_statsinks;
   std::vector<spdlog::sink_ptr> m_auditsinks;

   std::string m_pattern;

   SLogger *m_system;
   SLogger *m_s6as6d;
   SLogger *m_s6c;
   SLogger *m_s6t;
   SLogger *m_stat;
   SLogger *m_audit;
};

#endif // __LOGGER_H
