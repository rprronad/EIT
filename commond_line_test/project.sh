#!/bin/bash
<< Doc
Name		 : RAVIKUMAR
Date		 : 07/11/2022 
Description	 : Project: Command line Test 
Sample Input : 1.Sign in
			   2.sign up
			   3.Exit
			   Enter choice:

Sample Output: 1.Sign in
Doc
#################################################################################################################################
#!/bin/bash                                                  
function exam()                                       		 # Using function declaration and function name is exam
{
	clear
	echo -e "LS Test"				 				 		 # Display: LS Test
	echo -e "Test will Start after 10 second"		 		 # Display: Test will start after 10 second
	echo -e "ALL THE BEST"				  			 		 # Display: ALL THE BEST wishes to candidate
	Date=`date | cut -d " " -f4`			          		
	Month=`date | cut -d " " -f2`				
	Year=`date | cut -d " " -f7`				  			 # Display the Date
	echo -e "\t Date:$Date/$Month/$Year"
	sleep 5
	sed -i '1,11d' useranswer.txt				  			 # Deleting the txt content before storing the next useranswer.
	sed -i '1,200d' final_result.sh				  			 # Deleting the txt content before storing the next result.
	for i in `seq 5 5 50`					  				 # Total 50 lines of Question Bank.
	do
		cat question.txt | head -$i | tail -5    
		for j in `seq 10 -1 1`					  			 # 10sec Delay for each questions.
		do
			echo -e -n "\r Time left : $j \c \n"
			read -n 2 -t 1 -p "Enter option : " option		 # User give option for corresponding questions.
			if [ ${#option} -eq 1 ]
			then
				break						  				 # Break for if condition is true.
			fi
		done
		if [ ${#option} -eq 0 ]
		then
			option="e"
		fi
		echo $option >> useranswer.txt				  		 # Appending the user asnwers in useranswer.txt file
	done
	correct_answer=(`cat correct_answer.txt`)
	user_ans=(`cat useranswer.txt`)
	index=0
	count=0
	for i in `seq 5 5 50`						
	do
		cat question.txt | head -$i | tail -5 >> final_result.sh # Using the head and tail command display the question on screenone by one.
		for j in $index
		do
			if [ "${user_ans[$j]}" == "${correct_answer[$j]}" ]
			then
				echo -e "\e[32m Your answer is correct \e[0m" >> final_result.sh
				count=$(($count +1))
			elif [ "${user_ans[$j]}" == "e" ]
			then
				echo "timeout" >> final_result.sh
			else
				echo -e "\e[31m Your answer is incorrect you choose option ${user_ans[$j]} \e[0m" >> final_result.sh
				echo -e "\e[32m correct answer is ${correct_answer[$j]}\e[0m" >>final_result.sh
			fi
			index=$(($index +1))
		done
	done
	echo -e "\e[32m Your score is $count \e[0m" >> final_result.sh
	clear
	echo -e "\e[96m Your score will be updated within 5 seconds \e[0m"
	sleep 5
	echo -e "\e[1m \e[33m Result \e[0m \e[21m \e[0m"
	more final_result.sh					                # Final result.sh will display percentage wise on screen by using more command.
}
echo -e "\t\t\t\tPROJECT: COMMAND LINE TEST"               # PROJECT NAME
echo -e "1.Sign in :"			 
echo -e "2.Sign up :"
echo -e "3.Exit    :"
echo -e -n "Enter choice :"
read option
case $option in
	1) # Sign in
		echo -e -n "Please enter username :"; read username
		user=(`cat username.csv`)                           # Usernames are stored in username.csv file
			echo -e "\t\t ${user[@]}"
			length=${#user[@]}
			flag=0
			found=0
			for i in `seq 0 $(($length-1))`
			do
				if [ "$username" == "${user[$i]}" ]
				then 
					found=1
					echo -e -n "Enter 8 digit password :"; read -s password  # -s is the hiding the password 
					pass=(`cat password.csv`)
					echo -e "${pass[@]}"
					flag=2
					if [ "$password" == "${pass[$i]}" ]
					then
						echo "Start test"
						flag=1
						exam 			# Function calling: exam
						break
					fi
				fi
			done
			if [ $flag -eq 2 ]
			then
				echo -e "Incorrect password"
			fi
			if [ $found -eq 0 ]
			then
				echo -e "User is not present"
			fi
			;;
		2) # Sign up logic
			echo -e "Enter username :"
			read username			 
			user=(`cat username.csv`) # Username are stored in username.csv file
				count=0							
				print=0							
				len=${#user[@]}						
				echo -e "\t\t ${user[@]}"					 
				for i in ${user[@]}						
				do								
					if [ "${user[i]}" != "$username" ]				
					then							
						count=$(($count+1))					
					fi							
					if [ $count -eq $len ]			
					then							
						flag=0						
						echo $username >> username.csv          		
						echo -e "Enter password :"   
						read -s  password     	              # -s is the hiding the password.  
						echo -e "Confirm password :"          # This condition is to restrict the password with 8 number character.
						read -s  password1  	            	
						if [ ${#password} -ge 8 ]               		
						then			
							if [ "$password" == "$password1" ]		 
							then					
								echo $username >> username.csv  		
								echo $password >> password.csv  		
								echo -e "\e[32mSign up is successfully.!\e[0m" 		
							else					
								echo -e "Enter same matching password" 	 
							fi						
						else						
							echo -e "Enter minimum 8 number character password" 
						fi							
					else						
						if [ $print -eq 1 ]		
						then					
							echo -e "User is already Exist"		
							print=$(($print+1))			
						fi							
					fi						
				done							
				;;								
			3) 	
				exit
				;;
		esac

