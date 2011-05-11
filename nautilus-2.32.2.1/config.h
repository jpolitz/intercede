/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.in by autoheader.  */
/* #undef ENABLE_INSTALLER */
#define ENABLE_NLS 1
/* #undef ENABLE_PROFILER */
#define GETTEXT_PACKAGE "nautilus"
/* #undef HAVE_CATGETS */
#define HAVE_GETTEXT 1
#define HAVE_LC_MESSAGES 1
/* #undef HAVE_LIBBZ2 */
/* #undef HAVE_LIBJPEG */
/* #undef HAVE_MEDUSA */
/* #undef HAVE_STPCPY */
/* #undef bzclose */
/* #undef bzCompress */
/* #undef bzCompressInit */
/* #undef bzDecompress */
/* #undef bzDecompressInit */
/* #undef bzdopen */
/* #undef bzerror */
/* #undef bzflush */
/* #undef bzopen */
/* #undef bzread */
/* #undef bzwrite */
#define HAVE_GTK_MULTIHEAD /* needed for egg-screen-exec functions */
/* #undef HAVE_STARTUP_NOTIFICATION */
/* #undef HAVE_EXIF */
/* #undef HAVE_OLD_EXIF */
#define HAVE_RENDER 1

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* define to enable the empty view that is used for performance measurement */
/* #undef ENABLE_EMPTY_VIEW */

/* always defined to indicate that i18n is enabled */
#define ENABLE_NLS 1

/* define to enable PackageKit mimetype installer */
#define ENABLE_PACKAGEKIT 1

/* define to enable the profiler */
/* #undef ENABLE_PROFILER */

/* the gettext translation domain */
#define GETTEXT_PACKAGE "nautilus"

/* Define the location where the catalogs will be installed */
#define GNOMELOCALEDIR "/home/joe/share/locale"

/* Define to 1 if you have the `bind_textdomain_codeset' function. */
#define HAVE_BIND_TEXTDOMAIN_CODESET 1

/* Define to 1 if you have the `dcgettext' function. */
#define HAVE_DCGETTEXT 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to enable xmp support */
/* #undef HAVE_EXEMPI */

/* Define if we have exempi with the new API */
/* #undef HAVE_EXEMPI_NEW_API */

/* Define to enable EXIF support */
/* #undef HAVE_EXIF */

/* Define if the GNU gettext() function is already present or preinstalled. */
#define HAVE_GETTEXT 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define if your <locale.h> file defines LC_MESSAGES. */
#define HAVE_LC_MESSAGES 1

/* Define to 1 if you have the `m' library (-lm). */
#define HAVE_LIBM 1

/* Define to 1 if you have the <locale.h> header file. */
#define HAVE_LOCALE_H 1

/* Define to 1 if you have the <malloc.h> header file. */
#define HAVE_MALLOC_H 1

/* Define to 1 if you have the `mallopt' function. */
#define HAVE_MALLOPT 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define if your EXIF library has old API */
/* #undef HAVE_OLD_EXIF */

/* Define to 1 if libselinux is available */
/* #undef HAVE_SELINUX */

/* Define to 1 if you have the <selinux/selinux.h> header file. */
/* #undef HAVE_SELINUX_SELINUX_H */

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define if strftime supports %E and %O modifiers. */
#define HAVE_STRFTIME_EXTENSION 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/mount.h> header file. */
#define HAVE_SYS_MOUNT_H 1

/* Define to 1 if you have the <sys/param.h> header file. */
#define HAVE_SYS_PARAM_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/vfs.h> header file. */
#define HAVE_SYS_VFS_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the <X11/XF86keysym.h> header file. */
#define HAVE_X11_XF86KEYSYM_H 1

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Name of package */
#define PACKAGE "nautilus"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "http://bugzilla.gnome.org/enter_bug.cgi?product=nautilus"

/* Define to the full name of this package. */
#define PACKAGE_NAME "nautilus"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "nautilus 2.32.2.1"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "nautilus"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "2.32.2.1"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Version number of package */
#define VERSION "2.32.2.1"

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif

/* Define to 1 if the X Window System is missing or not being used. */
/* #undef X_DISPLAY_MISSING */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */
