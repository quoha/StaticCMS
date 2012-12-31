#include "Function.hpp"
#include "AST.hpp"
#include "Stack.hpp"
#include "Stream.hpp"
#include "SymbolTable.hpp"
#include "Template.hpp"
#include "Util.hpp"
#include "Variable.hpp"
#include <stdio.h>

//============================================================================
// LoadAllVarFunctions(symtab)
//
void NFTM::LoadAllFunctions(NFTM::SymbolTable *symtab) {
    if (!symtab) {
        return;
    }

    symtab->Add(new NFTM::VarBool("false", false));
    symtab->Add(new NFTM::VarBool("true", true));

    symtab->Add(new NFTM::VarFunction("bold"   , new NFTM::Func_Bold));
    symtab->Add(new NFTM::VarFunction("concat" , new NFTM::Func_Concat));
    symtab->Add(new NFTM::VarFunction("include", new NFTM::Func_Include));
    symtab->Add(new NFTM::VarFunction("not"    , new NFTM::Func_Not));
    symtab->Add(new NFTM::VarFunction("}"      , new NFTM::Func_PopStack));
    symtab->Add(new NFTM::VarFunction("{"      , new NFTM::Func_PushStack));
}

//============================================================================
// Execute(stack)
//
bool NFTM::Function::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    NFTM::OutputStream *errlog = symtab->ErrorLog();
    if (errlog) {
        errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
        errlog->Write("\tcalled VarFunction::Execute directly (or didn't override)\n");
    }
    return false;
}

//============================================================================
// Execute(stack)
//   t -- <bold> t </bold>
//
bool NFTM::Func_Bold::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (stack) {
        NFTM::StackItem *a = stack->Pop();
        
        if (!a) {
            NFTM::OutputStream *errlog = symtab->ErrorLog();
            if (errlog) {
                errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                errlog->Write("\tbold requires one item on the stack\n");
            }
            return false;
        }
        
        stack->PushText("<bold>");
        stack->Push(a);
        stack->PushText("</bold>");
    }
    return true;
}

//============================================================================
// Execute(stack)
//   t1 t2 -- t2t1
//
bool NFTM::Func_Concat::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (stack) {
        NFTM::StackItem *b = stack->Pop();
        NFTM::StackItem *a = stack->Pop();
        
        if (!a || !b) {
            NFTM::OutputStream *errlog = symtab->ErrorLog();
            if (errlog) {
                errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                errlog->Write("\tconcat requires two text items on the stack\n");
            }
            return false;
        }
        if (!stack->IsText(a) || !stack->IsText(b)) {
            NFTM::OutputStream *errlog = symtab->ErrorLog();
            if (errlog) {
                errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                errlog->Write("\tconcat requires two text items on the stack\n");
            }
            return false;
        }
        stack->PushText(NFTM::StrCat(b->u.text, a->u.text));
        delete a;
        delete b;
    }
    return true;
}

//============================================================================
// Execute(stack)
//  t -- <stack>
//
// reads in template file 't', executes it and places the result in a new stack
// that is pushed onto the current stack
//
bool NFTM::Func_Include::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (stack) {
        NFTM::StackItem *t = stack->Pop();
        
        if (!t) {
            NFTM::OutputStream *errlog = symtab->ErrorLog();
            if (errlog) {
                errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                errlog->Write("\tinclude requires at least one text item on the stack\n");
            }
            return false;
        }
        
        if (!stack->IsText(t)) {
            NFTM::OutputStream *errlog = symtab->ErrorLog();
            if (errlog) {
                errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                errlog->Write("\tinclude text item on the stack, not %s\n", "fix this reference to t->Kind()");
            }
            return false;
        }
        
        NFTM::TemplateFile *tmplt = new NFTM::TemplateFile(t->u.text);
        NFTM::AST *ast = tmplt->Load();
        if (!ast) {
            NFTM::OutputStream *errlog = symtab->ErrorLog();
            if (errlog) {
                errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                errlog->Write("\tinclude failed to load '%s'\n", t->u.text);
            }
            return false;
        }
        delete tmplt;
        
        NFTM::Stack *includeStack = new NFTM::Stack;
        if (!ast->Execute(symtab, includeStack)) {
            NFTM::OutputStream *errlog = symtab->ErrorLog();
            if (errlog) {
                errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                errlog->Write("\tinclude failed to execute '%s'\n", t->u.text);
            }
            return false;
        }
        
        stack->PushStack(includeStack);
        
        delete t;
    }
    return true;
}

//============================================================================
// Execute(stack)
//   false -- true
//   true  -- false
//   null  -- null
//
bool NFTM::Func_Not::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (stack) {
        NFTM::StackItem *a = stack->Pop();
        
        if (!a) {
            NFTM::OutputStream *errlog = symtab->ErrorLog();
            if (errlog) {
                errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                errlog->Write("\not requires one item on the stack\n");
            }
            return false;
        }
        
        // should really put real logic here
        //
        if (a->kind == siVariable) {
            stack->PushVarReference(new VarBool("boolean", true));
        } else {
            stack->PushVarReference(new VarBool("boolean", true));
        }
    }
    return true;
}

//============================================================================
// Execute(stack)
//  x <stackMarker> y z -- x { y z }
//
// searches stack for marker. removes the marker, moves everything from that
// point to a new stack and then pushes that stack onto the current stack
//
bool NFTM::Func_PopStack::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (stack) {
        // error if not found
        //
        if (!stack->CreateStack()) {
            NFTM::OutputStream *errlog = symtab->ErrorLog();
            if (errlog) {
                errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                errlog->Write("\tfailed to find matching '{' in stack\n");
            }
            return false;
        }
    }
    
    return true;
}

//============================================================================
// Execute(stack)
//  ~ -- ~ <stackMarker>
//
// pushes a stack marker onto the current stack
//
bool NFTM::Func_PushStack::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (stack) {
        stack->PushStackMarker();
    }
    return true;
}
