#include "enfield/Analysis/Nodes.h"

efd::Node::iterator efd::Node::begin() {
    return mChild.begin();
}

efd::Node::iterator efd::Node::end() {
    return mChild.end();
}

efd::Node::const_iterator efd::Node::begin() const {
    return mChild.begin();
}

efd::Node::const_iterator efd::Node::end() const {
    return mChild.end();
}

std::string efd::Node::getOperation() const {
    return "";
}

void efd::Node::print(std::ostream& O, bool pretty) {
    O << toString(pretty);
}

void efd::Node::print(bool pretty) {
    std::cout << toString(pretty);
}

std::string efd::Node::toString(bool pretty) const {
    std::string str(getOperation());

    for (auto Child : *this)
        str += " " + Child->toString(pretty);

    return str;
}

// -------------- Decl -----------------
efd::NDDecl::NDDecl(Type t) : mT(t) {
}

bool efd::NDDecl::isCReg() const {
    return mT == CONCRETE;
}

bool efd::NDDecl::isQReg() const {
    return mT == QUANTUM;
}

std::string efd::NDDecl::getOperation() const {
    switch (mT) {
        case CONCRETE: return "creg";
        case QUANTUM:  return "qreg";
    }
}

std::string efd::NDDecl::toString(bool pretty) const {
    std::string str(getOperation());

    str += " " + mChild[I_ID]->toString(pretty);
    str += "[" + mChild[I_SIZE]->toString(pretty) + "]";

    return str;
}

// -------------- GateDecl -----------------
efd::NDGateDecl::NDGateDecl() {
}

std::string efd::NDGateDecl::getOperation() const {
    return "gate";
}

std::string efd::NDGateDecl::toString(bool pretty) const {
    std::string str(getOperation());
    std::string endl = (pretty) ? "\n" : "";

    str += " " + mChild[I_ID]->toString(pretty);

    if (!mChild[I_ARGS]->mChild.empty())
        str += " (" + mChild[I_ARGS]->toString(pretty) + ")";

    str += " " + mChild[I_QARGS]->toString(pretty) + "{" + endl;
    str += mChild[I_GOPLIST]->toString(pretty) + endl + "}" + endl;

    return str;
}

// -------------- GOpList -----------------
efd::NDGOpList::NDGOpList() {
}

std::string efd::NDGOpList::toString(bool pretty) const {
    std::string str;
    std::string endl = (pretty) ? "\n" : "";
    std::string tab = (pretty) ? "\t" : "";

    for (auto Child : *this)
        str += tab + Child->toString(pretty) + ";" + endl;

    return str;
}

// -------------- Opaque -----------------
efd::NDOpaque::NDOpaque() {
}

std::string efd::NDOpaque::getOperation() const {
    return "opaque";
}

std::string efd::NDOpaque::toString(bool pretty) const {
    std::string str(getOperation());
    std::string endl = (pretty) ? "\n" : "";

    str += " " + mChild[I_ID]->toString(pretty);

    if (!mChild[I_ARGS]->mChild.empty())
        str += " (" + mChild[I_ARGS]->toString(pretty) + ")";

    str += " " + mChild[I_QARGS]->toString(pretty);

    return str;
}

// -------------- Qubit Operation: Measure -----------------
efd::NDQOpMeasure::NDQOpMeasure() {
}

std::string efd::NDQOpMeasure::getOperation() const {
    return "measure";
}

std::string efd::NDQOpMeasure::toString(bool pretty) const {
    std::string str(getOperation());
    std::string endl = (pretty) ? "\n" : "";

    str += " " + mChild[I_QBIT]->toString(pretty);
    str += " ->";
    str += " " + mChild[I_CBIT]->toString(pretty);

    return str;
}

// -------------- Qubit Operation: Reset -----------------
efd::NDQOpReset::NDQOpReset() {
}

std::string efd::NDQOpReset::getOperation() const {
    return "reset";
}

// -------------- Qubit Operation: Barrier -----------------
efd::NDQOpBarrier::NDQOpBarrier() {
}

std::string efd::NDQOpBarrier::getOperation() const {
    return "barrier";
}

// -------------- Qubit Operation: Call -----------------
efd::NDQOpCall::NDQOpCall() {
}

std::string efd::NDQOpCall::getOperation() const {
    return "measure";
}

std::string efd::NDQOpCall::toString(bool pretty) const {
    std::string str(getOperation());
    std::string endl = (pretty) ? "\n" : "";

    str += " " + mChild[I_QBIT]->toString(pretty);
    str += " ->";
    str += " " + mChild[I_CBIT]->toString(pretty);

    return str;
}

