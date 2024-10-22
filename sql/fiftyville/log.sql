-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Checking initial crime information
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = 'Humphrey Street';

-- Checking interviews conducted on the day
SELECT *
FROM interviews
WHERE month = 7 AND day = 28;

-- Investigating relevant responses obtained from the interrogated
-- Name: Ruth
SELECT *
FROM bakery_security_logs
WHERE month = 7
	AND activity = 'exit'
	AND day = 28
	AND hour = 10
	AND minute BETWEEN 15 AND 25;

-- Name: Eugene
SELECT *
FROM atm_transactions
WHERE year = 2023
	AND month = 7
	AND day = 28
	AND transaction_type = 'withdraw'
	AND atm_location = 'Leggett Street';

-- Name: Raymond
SELECT *
FROM phone_calls
WHERE year = 2023
	AND month = 7
	AND day = 28
	AND duration < 60;

-- Searching for the origin_airport_id of Fifty Ville
SELECT *
FROM airports;

-- Searching for the first flight leaving Fifty Ville the following day
SELECT *
FROM flights
WHERE year = 2023
	AND month = 7
	AND day = 29
	AND origin_airport_id = 8;

-- Identifying passengers on the flights
SELECT passengers.passport_number, people.name
FROM passengers
JOIN people ON passengers.passport_number = people.passport_number
WHERE passengers.flight_id IN (SELECT id FROM flights WHERE flight_id = 36 AND year = 2023 AND month = 7 AND day = 29);

-- Checking the personal data of the main suspects through their phone numbers
SELECT *
FROM people
WHERE phone_number IN (
	'(031) 555-6622',
	'(910) 555-3251'
);

-- Investigating Bruce
SELECT *
FROM people
WHERE license_plate = '94KL13X';

-- Investigating Luca
SELECT *
FROM people
WHERE license_plate = '4328GD8';

-- Checking once more by phone number
SELECT *
FROM people
WHERE phone_number = '(375) 555-8161';

-- Checking once more by phone number
SELECT *
FROM people
WHERE phone_number = '(389) 555-5198';
