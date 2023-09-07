DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
DIR=$(dirname "$(dirname "${DIR}")")

export BackendSOURCE="${DIR}/Backend/"
echo $BackendSOURCE
alias Banking="${BackendSOURCE}/build/Banking"

alias make_clean="rm build/* -r"

alias make="cmake --build ${BackendSOURCE}/build"
