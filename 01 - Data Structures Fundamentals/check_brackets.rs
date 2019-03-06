/*
    This is a rust implementation of the 
    bracket checking algorithm
*/
use std::io::stdin;

fn main() {
    let mut to_test = String::new();

    stdin().read_line(&mut to_test).expect("Error");

    to_test.pop(); // pop off \n at the end

    let balanced = match is_balanced(&to_test) {
        (true, _) => format!("is balanced"),
        (false, val) => format!("is not balanced and failed at character {}", val + 1)
    };
    println!("The String '{}' {}.", to_test, balanced);
}

fn is_balanced(text: &String) -> (bool, i32) {
    let mut balanced = true;
    let mut failed_at: i32 = -1;

    let mut stack: Vec<Bracket> = vec!();

    for (index, next) in text.chars().enumerate() {
        let index: i32 = index as i32;

        if Bracket::is_opening_bracket(next) {
            stack.push(Bracket::new(next, index));
        } else if Bracket::is_closing_bracket(next) {

            let b = match stack.pop(){
                Some(b) => b,
                None => {
                    balanced = false;
                    failed_at = index;
                    break;
                }
            };

            if !b.match_compl(next) {
                balanced = false;
                failed_at = index;
                break;
            }

        }
    }

    if balanced {
        balanced = stack.is_empty();
        if !balanced {
            let mut top: Bracket = Bracket::new(' ', -1);

            while let Some(t) = stack.pop(){ // try to get to the bottom of the stack and set
                top = t;                     // it's value to top
            }
            
            failed_at = top.position;
        }
    }

    return (balanced, failed_at);
}

struct Bracket {
    r#type: char,
    position: i32
}
impl Bracket {
    fn is_opening_bracket(c: char) -> bool {
        return match c {
            '{' |'['|'(' => true,
            _ => false
        }
    }
    fn is_closing_bracket(c: char) -> bool {
        return match c {
            '}' |']'|')' => true,
            _ => false
        }
    }
    fn new(r#type: char, position: i32) -> Self {
        return Bracket {r#type, position};
    }
    fn match_compl(&self, c: char) -> bool { // e.g.: type: '{' and c: '}' => true | t: '[', c: ')' => false 
        if self.r#type == '[' && c == ']' {
            return true;
        } 
        else if self.r#type == '(' && c == ')' {
            return true;
        }
        else if self.r#type == '{' && c == '}' {
            return true;
        }   
        else {
            return false;
        }
            
    }
}
