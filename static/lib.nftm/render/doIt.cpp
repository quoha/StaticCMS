#include "local.hpp"

//============================================================================
// DoIt(stream, stack)
//
bool NFTM::Render::DoIt(NFTM::OutputStream *os, NFTM::Stack *stack) {
    if (!os || !stack) {
        return false;
    }
#if 0
    NFTM::Variable *item = stack->Bottom();

    int counter = 0;

    while (item) {
        counter++;
        if (item->IsText()) {
            os->Write("%3d:\t %s\n", counter, item->AsText()->AsCString());
        } else if (item->IsStack()) {
            DoIt(os, item->AsStack());
        } else {
            os->Write("%3d\t don't know how to render %s.%s\n", counter, item->Kind(), item->Name());
        }
        item = stack->Bottom();
    }
#endif
	return true;
}
