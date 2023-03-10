// Copyright (c) 2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include <string>

#include "version.h"

// Name of client reported in the 'version' message. Report the same name
// for both bitcoind and bitcoin-qt, to make it harder for attackers to
// target servers or GUI users specifically.
const std::string CLIENT_NAME("KmushiUser");

// Client version number
#define CLIENT_VERSION_SUFFIX   "v1.3.6"


// The following part of the code determines the CLIENT_BUILD variable.
// Several mechanisms are used for this:
// * first, if HAVE_BUILD_INFO is defined, include build.h, a file that is
//   generated by the build environment, possibly containing the output
//   of git-describe in a macro called BUILD_DESC
// * secondly, if this is an exported version of the code, GIT_ARCHIVE will
//   be defined (automatically using the export-subst git attribute), and
//   GIT_COMMIT will contain the commit id.
// * then, three options exist for determining CLIENT_BUILD:
//   * if BUILD_DESC is defined, use that literally (output of git-describe)
//   * if not, but GIT_COMMIT is defined, use v[maj].[min].[rev].[build]-g[commit]
//   * otherwise, use v[maj].[min].[rev].[build]-unk
// finally CLIENT_VERSION_SUFFIX is added

// First, include build.h if requested
#ifdef HAVE_BUILD_INFO
#    include "build.h"
#endif


#ifndef BUILD_DATE
#    ifdef GIT_COMMIT_DATE
#        define BUILD_DATE GIT_COMMIT_DATE
#    else
#        define BUILD_DATE __DATE__ ", " __TIME__
#    endif
#endif

const std::string CLIENT_BUILD(CLIENT_VERSION_SUFFIX);
const std::string CLIENT_DATE(BUILD_DATE);
