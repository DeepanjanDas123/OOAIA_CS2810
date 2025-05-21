#include <bits/stdc++.h>
using namespace std;

class Book{

    private:
        string isbn;
        int copiesAvailable, totalCopies;

    public:
        string title, author;
        Book(string t = "UnknownTitle", string a = "UnknownAuthor", string i = "ISBN", int ca = 0, int tc = 5) : title(t), author(a), isbn(i), copiesAvailable(ca), totalCopies(tc) {}

        string getisbn(){
            return isbn;
        }

        int getca(){
            return copiesAvailable;
        }

        int gettc(){
            return totalCopies;
        }

        void updateCopies(int cnt){
            if(copiesAvailable + cnt < 0){
                cout<<"Invalid request! Count becomes negative\n";
                return;
            }
            copiesAvailable += cnt;
            totalCopies += cnt;
        }

        bool borrowBook(){
            if(copiesAvailable){
                copiesAvailable --;
                return true;
            }
            else{
                cout<<"Invalid request! Copy of book not available\n";
                return false;
            }
        }

        bool returnBook(){
            if(copiesAvailable < totalCopies){
                copiesAvailable++;
                return true;
            }
            else{
                cout<<"Invalid request! Copy of book exceeds total copies\n";
                return false;
            }
        }

        void printDetails(){
            cout<<title<<' '<<author<<'\n';
        }

        Book(Book &b, string ni) : title(b.title), author(b.author), isbn(b.isbn), copiesAvailable(b.copiesAvailable), totalCopies(b.totalCopies) {
            isbn = ni;
        } 

};

class Member{
    private:
        string memberID;
        map<string, int> borrowedBooks;
        int borrowLimit;
    public:
        string name;
        int currentBorrow = 0;
        Member(string mid = "mid", string n = "nm", int bl = 3) : memberID(mid), name(n), borrowLimit(bl) {}

        string getmemid(){
            return memberID;
        }

        bool borrowBook (string isbn){
            if(currentBorrow < borrowLimit){
                borrowedBooks[isbn]++;
                currentBorrow ++;
                return true;
            }
            else{
                cout<<"Invalid request! Borrow limit exceeded\n";
                return false;
            }
        }

        bool returnBook(string isbn){
            if(borrowedBooks.find(isbn) != borrowedBooks.end() && borrowedBooks[isbn] > 0){
                borrowedBooks[isbn]--;
                currentBorrow--;
                return true;
            }
            else{
                cout<<"Invalid request! Book not borrowed\n";
                return false;
            }
        }

        void printDetails(){
            if(borrowedBooks.empty()) return;
            for(auto p : borrowedBooks){
                if(p.second){
                    cout<<memberID<<' '<<name<<' '<<p.first<<' '<<p.second<<'\n';
                }
            }
        }
};

class Library{
    private:
        vector<Book> books;
        vector<Member> members;
        map<string, Book> book;
        map<string, Member> member;
    public:
        Book& bookexists(string isbn){
            return book[isbn];
        }
        Member& memberexists(string memid){
            return member[memid];
        }
        bool addBook(Book &b){
            if(book.find(b.getisbn()) != book.end()) {
                cout<<"Invalid request! Book with same isbn already exists\n";
                return false;
            }
            book[b.getisbn()] = b;
            books.push_back(b);
            return true;
        }

        bool registerMember(Member &m){
            if(member.find(m.getmemid()) != member.end()) {
                cout<<"Invalid request! Member with same id already exists\n";
                return false;
            }
            member[m.getmemid()] = m;
            members.push_back(m);
            return true;
        }

        bool borrowBook(string memid, string isbn){
            if(book.find(isbn) == book.end() || member.find(memid) == member.end()) return false;
            if(book[isbn].borrowBook()){
                if(member[memid].borrowBook(isbn)) return true;
                book[isbn].returnBook();
                return false;
            }
            return false;
        }

        bool returnBook(string memid, string isbn){
            if(book.find(isbn) == book.end() || member.find(memid) == member.end()) return false;
            if(book[isbn].returnBook()){
                if(member[memid].returnBook(isbn)) return true;
                book[isbn].borrowBook();
                return false;
            }
            return false;
        }

        void updateCopies(string isbn, int cnt){
            book[isbn].updateCopies(cnt);
        }

        void printLibraryDetails(){
            for(Book bk : books){
                cout<<bk.title<<' '<<bk.author<<' '<<book[bk.getisbn()].getca()<<'\n';
            }
            for(Member m : members){
                cout<<m.getmemid()<<' '<<m.name<<'\n';
            }
        }
};

int main() {
    Library l;
    while(true){
        string s;
        cin>>s;
        if(s == "Book"){
            string title;
            cin>>title;
            if(title == "None"){
                Book b;
                l.addBook(b);
                continue;
            }
            if(title == "ExistingBook"){
                string oi, ni;
                cin>>oi>>ni;
                Book b = l.bookexists(oi);
                Book bk(b, ni);
                l.addBook(bk);
                continue;
            }
            string author, isbn;
            int ca, tc;
            cin>>author>>isbn>>ca>>tc;
            Book bk(title, author, isbn, ca, tc);
            l.addBook(bk);
            continue;
        }
        if(s == "Member"){
            string s;
            cin>>s;
            if(s == "NoBorrowLimit"){
                string memid, name;
                cin>>memid>>name;
                Member m(memid, name);
                l.registerMember(m);
            }
            else{
                string name;
                int bl;
                cin>>name>>bl;
                Member m(s, name, bl);
                l.registerMember(m);
            }
        }
        if(s == "Borrow"){
            string memid, isbn;
            cin>>memid>>isbn;
            l.borrowBook(memid, isbn);
        }
        if(s == "PrintBook"){
            string isbn;
            cin>>isbn;
            Book b = l.bookexists(isbn);
            b.printDetails();
        }
        if(s == "PrintMember"){
            string memid;
            cin>>memid;
            Member m = l.memberexists(memid);
            m.printDetails();
        }
        if(s == "PrintLibrary"){
            l.printLibraryDetails();
        }
        if(s == "Return"){
            string memid, isbn;
            cin>>memid>>isbn;
            l.returnBook(memid, isbn);
        }
        if(s == "UpdateCopiesCount"){
            string isbn;
            int cnt;
            cin>>isbn>>cnt;
            l.updateCopies(isbn, cnt);
        }
        if(s == "Done") break;
        else continue;
    }
    return 0;
}