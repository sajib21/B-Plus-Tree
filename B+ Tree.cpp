#include<bits/stdc++.h>
#define vi      vector<int>
#define vp      vector<node*>
#define pb(x)   push_back(x)
#define pp()    pop_back()
#define MAXN    4
#define LIM     100005

using namespace std;


/* 1 100 1 500 1 1000 1 000 1 600 1 010 1  300 1 2000
   1 700 1 800 1 2000 1 025 1 050 1 080 1 1500 1 2500

   1 100 1 200 1 300 1 400 1 130 1 160 1 000 1 050

   1 5000 1 2500 1 5000 1 3000 */

void instr() {
    cout << "PRESS 1 TO INSERT A VALUE." << endl;
    cout << "PRESS 2 TO DELETE A VALUE." << endl;
    cout << "PRESS 3 TO TRAVERSE DFS WISE." << endl;
    cout << "PRESS 4 TO TRAVERSE BFS WISE." << endl;
    cout << "PRESS 5 TO SEARCH A VALUE." << endl;
}

struct node {
    int sz=0, szp=0;
    int val[MAXN+3];
    node* ptr[MAXN+3];
    node* par;
    node* sibling;
    int parPtrID;
    bool isLeaf;

    node* create() {
        node* cur = (node*)malloc(sizeof (node));
        cur->sz = 0; cur->szp = 0;
        cur->isLeaf = true;
        cur->par = NULL;
        cur->sibling = NULL;
        cur->parPtrID = -1;
//        cout << "New Tree Created!" << endl;
        return cur;
    }

    void insertVal(int in, int x) {
        for(int i=sz-1; i>=in; i--) val[i+1] = val[i];
        val[in] = x;
        sz++;
    }
    void insertPtr(int in, node* p) {
        for(int i=szp-1; i>=in; i--) {
            ptr[i]->parPtrID++;
            ptr[i+1] = ptr[i];
//            ptr[i]->parPtrID++;
        }
        ptr[in] = p;
        szp++;
    }

    void pushBackVal(int x) {
        val[sz++] = x;
    }
    void pushBackPtr(node* p) {
        ptr[szp++] = p;
    }

    void eraseVal(int in) {
        for(int i=in+1; i<sz; i++) val[i-1] = val[i];
        sz--;
    }
    void erasePtr(int in) {
        for(int i=in+1; i<szp; i++) ptr[i-1] = ptr[i];
        szp--;
    }

    void reverseVal() {
        reverse(val, val+sz);
    }
    void reversePtr() {
        reverse(ptr, ptr+szp);
    }

    void insert(int x) {
        int iny=0;
        while(iny < sz) {
            if(x < val[iny]) break;
            iny++;
        }

        if(isLeaf) insertVal(iny, x);
        else {
//            cout << "INS " << iny << endl;
            ptr[iny]->insert(x);
        }

        if(sz == MAXN) split();
    }

    void split() {
        node* splitedNode = create();
        splitedNode->isLeaf = isLeaf;
        sibling = splitedNode;

        while(sz > MAXN/2) {
            splitedNode->pushBackVal(val[sz-1]);
            sz--; ///val.pp();
        }
        while(szp > MAXN/2+1) {
            splitedNode->pushBackPtr(ptr[szp-1]);
            szp--; ///ptr.pp();
        }
        splitedNode->reverseVal();
        splitedNode->reversePtr();
        for(int i=0; i<splitedNode->szp; i++) {
            splitedNode->ptr[i]->parPtrID = i;
            splitedNode->ptr[i]->par = splitedNode;
        }

        ///notun root
        if(par == NULL) {
            par = create();
            par->isLeaf = false;
            par->pushBackPtr(this);
            parPtrID = 0;
        }

        splitedNode->par = par;
        splitedNode->parPtrID = parPtrID+1;

//        cout << "PARPTR " << parPtrID << endl;

        ///handle parent er majhkhane insert
        par->insertVal(parPtrID, splitedNode->val[0]);
        par->insertPtr(parPtrID+1, splitedNode);

        ///handle leaf na hoile split thk 0 er ta delete
        if(!isLeaf) splitedNode->eraseVal(0);

//        cout << "AFTER SPLIT" << endl;
//        for(int i=0; i<sz; i++) cout << val[i] << ' ' ; cout << endl;
//        for(int i=0; i<splitedNode->sz; i++) cout << splitedNode->val[i] << ' ' ; cout << endl;
//        for(int i=0; i<par->sz; i++) cout << par->val[i] << ' ' ; cout << endl;
    }

    void remove(int x) {
        printNode();
        int iny=sz-1;
        while(iny >= 0 && x < val[iny]) {
//            if(x < val[iny]) break;
            iny--;
        }
        iny++;
//        cout << "GOTO " << iny << endl;
        if(isLeaf) {
            iny--;
            if(iny>=0 && val[iny] == x) {
//                if(iny == 0 && parPtrID) par->val[parPtrID-1] = val[iny+1];
                eraseVal(iny);
                if(sz < MAXN/2) {
                    if(borrowFromRight()) return;
//                    if(borrowFromRight()) return;
//                    redistribute();
                }
            }
            else cout << "VALUE NOT FOUND!" << endl;
        }
        else {
            ptr[iny]->remove(x);
        }
    }

    void search(int x) {
        printNode();
        int iny=sz-1;
        while(iny >= 0 && x < val[iny]) {
            iny--;
        }
        iny++;
        if(isLeaf) {
            iny--;
            if(val[iny] == x) {
                cout << "VALUE FOUND!" << endl;
            }
            else cout << "VALUE NOT FOUND!" << endl;
        }
        else {
            cout << "GOTO: " << iny << endl;
            ptr[iny]->search(x);
        }
    }

    bool borrowFromRight() {
        if(parPtrID+1 == par->szp) return false; ///right sibling nai
        node* rgt = par->ptr[parPtrID+1];
        if(rgt->sz) {

        }
    }

//    bool borrowFromLeft() {
//        if(parPtrID == 0) return false;
//        node* leftSib = par->ptr[parPtrID-1];
//        if(leftSib.sz < MAXN/2)
//    }

    void dfsTraverse() {
        printNode();
        for(int i=0; i<szp; i++) {
            if(ptr[i] != NULL) {
                cout << "Goto " << i << " : " << endl; getchar();
                ptr[i]->dfsTraverse();
            }
        }
    }

    void bfsTraverse() {
        queue<node*>q;
        q.push(this);
        q.push(NULL);

        bool leafFound = false;

        while(!q.empty()) {
            node* cur = q.front();
            q.pop();

            if(cur != NULL && cur->isLeaf) leafFound = true;

            if(cur == NULL) {
                cout << endl;
                if(leafFound) break;
                q.push(NULL);
                continue;
            }

            cur->printVal();
            for(int i=0; i<cur->szp; i++) q.push(cur->ptr[i]);
        }
    }

    void printNode() {
        cout << "DFS: " << endl;
        cout << "PARPTR: " << parPtrID << endl;
        cout << "Val: " << sz << " Ptr: " << szp << " isLeaf: " << isLeaf << endl;
        cout << "Values: ";
        for(int i=0; i<sz; i++) cout << val[i] << ' '; cout << endl;
        getchar();
    }
    void printVal() {
        for(int i=0; i<sz; i++) cout << val[i] << ' ';
        cout << "  ||  " ;
    }
};

//node* tree = NULL;

int main() {
    node* tree;
    tree = tree->create();

    instr();

    int op;
    while(scanf("%d", &op) && op) {
        int x;
        if(op == 1) {
            cout << "WHAT DO YOU WANT TO INSERT: " ;

            scanf("%d", &x);

//            x = rand() % 1000;
//            printf("%d\n", x);
//            getchar();

            tree->insert(x);
            while(tree->par != NULL) {
                tree = tree->par;
            }
        }
        else if(op == 2) {
            cout << "WHAT DO YOU WANT TO ERASE: ";
            scanf("%d", &x);
            tree->remove(x);
        }
        else if(op == 3) {
            tree->dfsTraverse();
        }
        else if(op == 4) {
            tree->bfsTraverse();
        }
        else if(op == 5) {
            cout << "WHAT DO YOU WANT TO FIND: " ;
            scanf("%d", &x);
            tree->search(x);
        }

        instr();
    }

}
