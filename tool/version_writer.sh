#!/bin/sh

GIT_DIR="${1}/.git"

if [ "x" = "x${GIT}" ]
then
	if ! GIT=$(which git)
	then
	 	GIT=""
	fi
fi
if [  -e "${GIT}"  ]
then
	GITVERSION=$( ${GIT} --git-dir="${GIT_DIR}" describe --always --tag | tr -d "\n\r" )
else
	#fallback version string with date
	GITVERSION="NOGIT`date +%s`"
fi

printf \
"#include <%s/version.h>\n\n"\
"namespace %s\n"\
"{\n\n"\
"const std::string Version::project_name = \"%s\";\n"\
"const std::string Version::git_tag      = \"%s\";\n"\
"const std::string Version::build_date   = __DATE__;\n\n"\
"}\n" ${2} ${2} ${3} ${GITVERSION}
