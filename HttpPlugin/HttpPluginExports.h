#ifndef HTTP_PLUGIN_EXPORTS_H__
#define HTTP_PLUGIN_EXPORTS_H__

#ifdef _MSC_VER
#define HTTPPLUGIN_EXPORT_DECLSPEC extern "C" __declspec(dllexport)
#define HTTPPLUGIN_IMPORT_DECLSPEC extern "C" __declspec(dllimport)
#define HTTPPLUGIN_CLASS_EXPORT_DECLSPEC __declspec(dllexport)
#define HTTPPLUGIN_CLASS_IMPORT_DECLSPEC __declspec(dllimport)
#endif // _MSC_VER

#ifdef __GNUC__
#define HTTPPLUGIN_EXPORT_DECLSPEC __attribute__ ((visibility("default")))
#define HTTPPLUGIN_IMPORT_DECLSPEC
#define HTTPPLUGIN_CLASS_EXPORT_DECLSPEC __attribute__ ((visibility("default")))
#define HTTPPLUGIN_CLASS_IMPORT_DECLSPEC 
#endif


#ifdef HTTPPLUGIN_EXPORTS
#define HTTPPLUGIN_DECLSPEC HTTPPLUGIN_EXPORT_DECLSPEC
#define HTTPPLUGIN_CLASS_DECLSPEC HTTPPLUGIN_CLASS_EXPORT_DECLSPEC
#else
#define HTTPPLUGIN_DECLSPEC HTTPPLUGIN_IMPORT_DECLSPEC
#define HTTPPLUGIN_CLASS_DECLSPEC HTTPPLUGIN_CLASS_IMPORT_DECLSPEC
#endif

#endif // HTTP_PLUGIN_EXPORTS_H__