#include <iostream>
#include <string.h>

const int NAME_SIZE = 64, GENRE_SIZE = 16, TITLE_SIZE = 64;

enum class Genre{
    horror,
    realism,
    fantasy
};

const char* genres[] = {"horror", "realism", "fantasy"};

struct Book{
    char authorName[NAME_SIZE];
    Genre genre;
    char title[TITLE_SIZE];
    unsigned short year;
};

void fillLibrary(Book *library, const unsigned int numberOfBooks){
    for(std::size_t i = 0; i < numberOfBooks; i++){
        std::cout << "Enter the author's name:" << std::endl;
        std::cin.getline(library[i].authorName, NAME_SIZE);
        std::cout << "Enter 0 for horror, 1 for realism or 2 for fantasy:" << std::endl;
        int genreIndex;
        std::cin >> genreIndex;
        std::cin.ignore();
        switch (genreIndex)
        {
        case 0:
            library[i].genre = Genre::horror;
            break;
        case 1:
            library[i].genre = Genre::realism;
            break;
        case 2:
            library[i].genre = Genre::fantasy;
            break;
        default:
            break;
        }
        std::cout << "Enter the title of the book:" << std::endl;
        std::cin.getline(library[i].title, TITLE_SIZE);
        std::cout << "Enter the year of publishing:" << std::endl;
        std::cin >> library[i].year;
        std::cin.ignore();
    }
}

void printBook(const Book &book){
    std::cout << book.authorName << " " << genres[(int)book.genre] << " " << book.title << " " << book.year << std::endl;
}

void printBooksByAuthor(const Book *library, const unsigned int numberOfBooks, const char *authorName){
    for(std::size_t i = 0; i < numberOfBooks; i++){
        if(strcmp(authorName, library[i].authorName) == 0) std::cout << library[i].title << " ";
    }
    std::cout << std::endl;
}
void printMostPublishedBooks(const Book *library, const unsigned int numberOfBooks, const int year){
    int countPrime = -1;
    char mostPublished[NAME_SIZE];
    for(std::size_t i = 0; i < numberOfBooks; i++){
        int count = 0;
        if(library[i].year == year){
            for(std::size_t j = 0; j < numberOfBooks; j++){
                if(strcmp(library[i].authorName, library[j].authorName) == 0){
                    count++;
                }
            }
        }
        if(count > countPrime){
            countPrime = count;
            strcpy(mostPublished, library[i].authorName);
            mostPublished[strlen(library[i].authorName)] = '\0';
        }

    }
    std::cout << mostPublished << std::endl;
}
void printLastPublishedBook(const Book *library, const unsigned int numberOfBooks, const char *author){
    char lastBook[TITLE_SIZE];
    int max = -99999;
    for(std::size_t i = 0; i < numberOfBooks; i++){
        if((strcmp(library[i].authorName, author) == 0) && (max < library[i].year)){
            max = library[i].year;
            strcpy(lastBook, library[i].title);
        }
    }
    std::cout << lastBook << std::endl;
}

void printMostPopularGenreInYear(const Book *library, const unsigned int numberOfBooks, const int year){
    int countPrime = -1;
    Genre mostPopular;
    for(std::size_t i = 0; i < numberOfBooks; i++){
        int count = 0;
        if(library[i].year == year){
            for(std::size_t j = 0; j < numberOfBooks; j++){
                if((int)library[i].genre == (int)library[j].genre){
                    count++;
                }
            }
        }
        if(count > countPrime){
            countPrime = count;
            mostPopular = library[i].genre;
        }

    }
    std::cout << genres[(int)mostPopular] << std::endl;
}

int main(){
    std::cout << "Enter number of books: " << std::endl;
    unsigned int numberOfBooks;
    std::cin >> numberOfBooks;
    std::cin.ignore();
    Book *library = new Book[numberOfBooks];
    fillLibrary(library, numberOfBooks);
    printMostPopularGenreInYear(library, numberOfBooks, 2003);
    delete [] library; // не знам как да изтрия поотделно структурите в масива
    return 0;
}
