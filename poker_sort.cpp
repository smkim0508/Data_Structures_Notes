#include <iostream>
#include <vector>

int findMax(int arr[], int n)
{
	int mx = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] > mx) {
			mx = arr[i];
        }    
    }        
	return mx;
}

void countingSort(int main_arr[], int correspond[], int n, int exp)
{
	int* sorted = new int[n]; // the new array that will be the sorted output of the main array
    int* map = new int[n]; // the array that is mapped corresponding to the sort
	int i, count[10] = { 0 };

	for (i = 0; i < n; i++) {
		count[(main_arr[i] / exp) % 10]++;
    }

	for (i = 1; i < 10; i++) {
		count[i] += count[i - 1];
    }

	for (i = n - 1; i >= 0; i--) {
		sorted[count[(main_arr[i] / exp) % 10] - 1] = main_arr[i];
        map[count[(main_arr[i] / exp) % 10] - 1] = correspond[i];
		count[(main_arr[i] / exp) % 10]--;
	}

	for (i = 0; i < n; i++) {
		main_arr[i] = sorted[i];
        correspond[i] = map[i];
    }
}

void radixsort(int main_arr[], int correspond[], int n)
{
	int m = findMax(main_arr, n);

	for (int exp = 1; m / exp > 0; exp *= 10) {
        countingSort(main_arr, correspond, n, exp);
    }
		
}

void reverse(int arr[], int n)
{
    int reversed[n];
    for (int i = 0; i < n; i ++) {
        reversed[i] = arr[n-1-i];
    }

    for (int i = 0; i < n; i++)
		arr[i] = reversed[i];

}

int power(int hand) {

    int cards[5];
    int dummy[5] = {0};
    
    for (int i=0; i<5; i++) {
        cards[i] = hand % 52;
        hand /= 52;
    }

    radixsort(cards, dummy, 5);
    reverse(cards, 5);

    bool is_flush = true;
    int flush_rank = 0;

    for (int i=1; i<5; i++) {
        if (cards[i] % 4 != cards[0] % 4) {
            is_flush = false;
            break;
        }
    }   

    if (is_flush) {
        for (int i=0; i<5; i++) {
            flush_rank += (cards[i]/4);
            flush_rank *= 13;
        }
        flush_rank /= 13;
    }

    bool is_straight = true;
    int straight_rank = 0;

    for (int i=0; i<4; i++) {
        if (i == 0 && cards[0]/4 == 12 && cards[1]/4 == 3) {
            continue;
        }
        
        if ((cards[i] / 4) != ((cards[i+1] / 4) + 1)) {
            is_straight = false;
            break;
        }
    }

    if (is_straight) {
       
        if (cards[0]/4 == 12 && cards[1]/4 == 3) {
            straight_rank = 1;
        }

        else { 
            straight_rank = (cards[0]/4) - 2;
        }
    }
     
    bool is_four_of_kind = false;
    int four_of_kind_rank = 0;

    if (cards[0]/4 == cards[3]/4 || cards[1]/4 == cards[4]/4) {
        is_four_of_kind = true;
    }

    if (is_four_of_kind) {
        if (cards[0]/4 == cards[3]/4) {
            four_of_kind_rank = (cards[0]/4 * 13) + cards[4]/4;
        }
        if (cards[1]/4 == cards[4]/4) {
            four_of_kind_rank = (cards[1]/4 * 13) + cards[0]/4;
        }
    }

    bool is_full_house = false;
    int full_house_rank = 0;

    if ((cards[0]/4 == cards[2]/4 && cards[3]/4 == cards[4]/4) || (cards[0]/4 == cards[1]/4 && cards[2]/4 == cards[4]/4)) {
        is_full_house = true;
    } 

    if (is_full_house) {
        if (cards[0]/4 == cards[2]/4 && cards[3]/4 == cards[4]/4) {
            full_house_rank = cards[0]/4 * 13 + cards[3]/4;
        }
        else {
            full_house_rank = cards[2]/4 * 13 + cards[0]/4;
        }
    }

    bool is_three_of_kind = false;
    int three_of_kind_rank = 0;

    if (cards[0]/4 == cards[2]/4 || cards[1]/4 == cards[3]/4 || cards[2]/4 == cards[4]/4) {
        is_three_of_kind = true;
    }
    
    if (is_three_of_kind) {
        if (cards[0]/4 == cards[2]/4) {
            three_of_kind_rank = cards[0]/4 * 13 * 13 + cards[3]/4 * 13 + cards[4]/4;
        }
        else if (cards[1]/4 == cards[3]/4) {
            three_of_kind_rank = cards[1]/4 * 13 * 13 + cards[0]/4 * 13 + cards[4]/4;
        }
        else {
            three_of_kind_rank = cards[2]/4 * 13 * 13 + cards[0]/4 * 13 + cards[1]/4;
        }
    }

    bool is_two_pair = false;
    int two_pair_rank = 0;

    if ((cards[0]/4 == cards[1]/4 && cards[2]/4 == cards[3]/4) || (cards[0]/4 == cards[1]/4 && cards[3]/4 == cards[4]/4) || (cards[1]/4 == cards[2]/4 && cards[3]/4 == cards[4]/4)) {
        is_two_pair = true;
    }

    if (is_two_pair) {
        if (cards[0]/4 == cards[1]/4 && cards[2]/4 == cards[3]/4) {
            two_pair_rank = cards[0]/4 * 13 * 13 + cards[2]/4 * 13 + cards[4]/4;
        }
        else if (cards[0]/4 == cards[1]/4 && cards[3]/4 == cards[4]/4) {
            two_pair_rank = cards[0]/4 * 13 * 13 + cards[3]/4 * 13 + cards[2]/4;
        }
        else {
            two_pair_rank = cards[1]/4 * 13 * 13 + cards[3]/4 * 13 + cards[0]/4;
        }
    }

    bool is_pair = false;
    int pair_rank = 0;

    for (int i=0; i<4; i++) {
        if (cards[i]/4 == cards[i+1]/4) {
            is_pair = true;
            break;
        }
    }

    if (is_pair) {
        if (cards[0]/4 == cards[1]/4) {
            pair_rank = cards[0]/4 * 13 * 13 * 13 + cards[2]/4 * 13 * 13 + cards[3]/4 * 13 + cards[4]/4;
        }
        else if (cards[1]/4 == cards[2]/4) {
            pair_rank = cards[1]/4 * 13 * 13 * 13 + cards[0]/4 * 13 * 13 + cards[3]/4 * 13 + cards[4]/4;
        }
        else if (cards[2]/4 == cards[3]/4) {
            pair_rank = cards[2]/4 * 13 * 13 * 13 + cards[0]/4 * 13 * 13 + cards[1]/4 * 13 + cards[4]/4;
        }
        else {
            pair_rank = cards[3]/4 * 13 * 13 * 13 + cards[0]/4 * 13 * 13 + cards[1]/4 * 13 + cards[2]/4;
        }
    }
    
    if(is_straight && is_flush) return 3040000 + straight_rank;
    else if(is_four_of_kind) return 2660000 + four_of_kind_rank;
    else if (is_full_house) return 2280000 + full_house_rank;
    else if(is_flush) return 1900000 + flush_rank;
    else if(is_straight) return 1520000 + straight_rank;
    else if (is_three_of_kind) return 1140000 + three_of_kind_rank;
    else if (is_two_pair) return 760000 + two_pair_rank;
    else if (is_pair) return 380000 + pair_rank;
    else return cards[0]/4 * 13 * 13 * 13 * 13 + cards[1]/4 * 13 * 13 * 13 + cards[2]/4 * 13 * 13 + cards[3]/4 * 13 + cards[4]/4;   

}

void poker_sort(std::vector<int>& a) {
    
    int n = a.size();
    int score[n];
    int correspond[n];
    
    for (int i=0; i<n; i++) {
        score[i] = power(a[i]);
        correspond[i] = a[i];
        // std::cout << score[i] << " " << correspond[i] << std::endl;
    }

    radixsort(score, correspond, n);
        
    for (int i=0; i<n; i++) {
        a[i] = correspond[i];
    }

};
