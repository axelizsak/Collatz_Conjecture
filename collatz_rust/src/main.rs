use std::io;

fn collatz_sequence(num: i32) -> Vec<i32> {
    let mut sequence: Vec<i32> = Vec::new();
    let mut n = num;

    // Generate the Collatz sequence until n reaches 1
    while n != 1 {
        sequence.push(n);

        // Apply the Collatz rule: if n is even, divide it by 2; otherwise, multiply by 3 and add 1
        if n % 2 == 0 {
            n /= 2;
        } else {
            n = 3 * n + 1;
        }
    }

    sequence.push(n);
    sequence
}

fn int_to_binary(n: i32) -> String {
    // Convert an integer to its binary representation
    format!("{:b}", n)
}

fn binary_to_decimal(binary: &str) -> Result<i32, std::num::ParseIntError> {
    // Convert a binary string to its decimal representation
    i32::from_str_radix(binary, 2)
}

fn is_binary(binary: &str) -> bool {
    // Check if a string represents a valid binary number (contains only '0' and '1')
    binary.chars().all(|c| c == '0' || c == '1')
}

fn collatz_sequence_check(numbers: &[i32]) {
    if numbers.is_empty() {
        println!("No numbers provided");
        return;
    }

    // Check the first criterion: Do we have a binary representation of the first term of the collatz trace?
    let bin_first = match binary_to_decimal(&int_to_binary(numbers[0])) {
        Ok(bin_num) => bin_num,
        Err(_) => {
            println!("Error converting the first binary value to decimal");
            return;
        }
    };
    let test1 = bin_first - numbers[0];
    if test1 == 0 {
        println!("Criterion 1: OK");
    } else {
        println!("Criterion 1: Error");
    }

    // Check the second criterion: Is the last term a binary representation of 1?
    let bin_last = match binary_to_decimal(&int_to_binary(numbers[numbers.len() - 1])) {
        Ok(bin_num) => bin_num,
        Err(_) => {
            println!("Error converting the last binary term to decimal");
            return;
        }
    };
    let test2 = bin_last - 1;
    if test2 == 0 {
        println!("Criterion 2: OK");
    } else {
        println!("Criterion 2: Error");
    }

    // Check the third criterion: Does the trace contain only bits? (0 or 1)
    let all_binaries_are_binary = numbers.iter().all(|&num| is_binary(&int_to_binary(num)));
    if all_binaries_are_binary {
        println!("Criterion 3: OK");
    } else {
        println!("Criterion 3: Error");
    }

    let mut z = 1;
    // Check the fourth criterion: Is the collatz rule verified between each number?
    for i in 0..numbers.len() - 1 {
        let bin1 = match binary_to_decimal(&int_to_binary(numbers[i])) {
            Ok(bin_num) => bin_num,
            Err(_) => {
                println!("Error converting the binary value to decimal");
                return;
            }
        };

        let bin2 = match binary_to_decimal(&int_to_binary(numbers[i + 1])) {
            Ok(bin_num) => bin_num,
            Err(_) => {
                println!("Error converting the binary value to decimal");
                return;
            }
        };

        let result = if bin1 % 2 == 0 {
            bin1 - (2 * bin2)
        } else {
            (3 * bin1 + 1) - bin2
        };

        if result != 0 {
            println!("Criterion 4: Error -> {} {}", numbers[i], numbers[i + 1]);
            z -= 1;
        }
    }
    if z == 1 {
        println!("Criterion 4: OK");
    }
}

fn main() {
    println!("Please enter a positive integer:");
    let mut input = String::new();
    io::stdin()
        .read_line(&mut input)
        .expect("Error reading input");

    let num: i32 = input.trim().parse().expect("Please enter a valid integer");

    let sequence = collatz_sequence(num);
    println!("Result: {:?}", sequence);

    collatz_sequence_check(&sequence);
}