-- Keep a log of any SQL queries you execute as you solve the mystery.
-- TODO: Identify:
-- TODO: - Who the thief is
-- TODO: - Where the thief escaped to
-- TODO: - Who the thief's accomplice was who helped them escape town
-- The only information I have is that the theft took place on July 28,
-- 2021 and that it took place on Humphrey Street.
-- The first thing that comes to mind is to search for crimes that occurred on July 28, 2021 on Humphrey Street.
   SELECT id,
          description
     FROM crime_scene_reports
    WHERE YEAR = 2021
      AND MONTH = 7
      AND DAY = 28
      AND street = 'Humphrey Street';

-- With the previous query, I could see that the id of the robbery is 295, it took place at 10:15am, that there were 3 witnesses, and that all of them mentioned a bakery.
-- I'm going to search for interviews that happened on the same day as the crime mentioning a bakery.
   SELECT id,
          name AS witness,
          transcript
     FROM interviews
    WHERE transcript LIKE '%bakery%'
      AND YEAR = 2021
      AND MONTH = 7
      AND DAY = 28;

-- The information I obtained was:
--    Ruth: The thief got into a car and left the bakery parking lot within ten minutes of the theft.
--  Eugene: He recognized the thief earlier in the morning at an ATM on Leggett Street, withdrawing money.
-- Raymond: The thief made a phone call just as they were leaving the bakery.
--          During the call, the thief mentioned planning to take the earliest flight out of Fiftyville the next day.
--          The thief asked the person on the other end of the phone to purchase the flight ticket.
-- According to the information given by Ruth, I should check the security footage from the bakery parking lot to identify the cars that left within the specified ten-minute window after the theft occurred.
   SELECT id,
          HOUR,
          MINUTE,
          activity,
          license_plate
     FROM bakery_security_logs
    WHERE YEAR = 2021
      AND MONTH = 7
      AND DAY = 28
      AND HOUR = 10
      AND MINUTE >= 15
      AND MINUTE <= 25;

-- I obtained the plates of 8 people leaving the bakery
-- Based on Eugene's information, I'm investigating ATM transactions that occurred on Leggett Street on a specific day.
-- I've collected the account numbers of 8 individuals who made withdrawals.
-- I'm now retrieving the information associated with those bank accounts.
   SELECT person_id,
          account_number,
          creation_year
     FROM bank_accounts
    WHERE account_number IN (
             SELECT account_number
               FROM atm_transactions
              WHERE YEAR = 2021
                AND MONTH = 7
                AND DAY = 28
                AND atm_location = 'Leggett Street'
                AND transaction_type = 'withdraw'
          );

-- According to the information given by Raymond I should check for a call on that day that lasted less than 1 minute
-- and the earliest flight the next day of the robbery, the person who bought the ticket was the person who called the thief.
   SELECT id,
          caller,
          receiver
     FROM phone_calls
    WHERE YEAR = 2021
      AND MONTH = 7
      AND DAY = 28
      AND duration <= 60;

-- I obtained the phone numbers of 20 people
-- I should retrieve the id, and the origin and destination airports of the earliest flight on July 29, 2021
   SELECT id,
          origin_airport_id,
          destination_airport_id
     FROM flights
    WHERE YEAR = 2021
      AND MONTH = 7
      AND DAY = 29
 ORDER BY HOUR,
          MINUTE
    LIMIT 1;

-- I should retrieve the passport number on that flight
   SELECT passport_number,
          seat
     FROM passengers
    WHERE flight_id in (
             SELECT id
               FROM flights
              WHERE YEAR = 2021
                AND MONTH = 7
                AND DAY = 29
           ORDER BY HOUR,
                    MINUTE
              LIMIT 1
          );

-- With all of that information I should get who the thief is
   SELECT name AS thief_name
     FROM people
    WHERE license_plate IN (
             SELECT license_plate
               FROM bakery_security_logs
              WHERE YEAR = 2021
                AND MONTH = 7
                AND DAY = 28
                AND HOUR = 10
                AND MINUTE >= 15
                AND MINUTE <= 25
          )
      AND phone_number IN (
             SELECT caller
               FROM phone_calls
              WHERE YEAR = 2021
                AND MONTH = 7
                AND DAY = 28
                AND duration <= 60
          )
      AND id IN (
             SELECT person_id
               FROM bank_accounts
              WHERE account_number IN (
                       SELECT account_number
                         FROM atm_transactions
                        WHERE YEAR = 2021
                          AND MONTH = 7
                          AND DAY = 28
                          AND atm_location = 'Leggett Street'
                          AND transaction_type = 'withdraw'
                    )
          )
      AND passport_number IN (
             SELECT passport_number
               FROM passengers
              WHERE flight_id = (
                       SELECT id
                         FROM flights
                        WHERE YEAR = 2021
                          AND MONTH = 7
                          AND DAY = 29
                     ORDER BY HOUR,
                              MINUTE
                        LIMIT 1
                    )
          );

-- Where the thief escaped to
   SELECT city AS thief_escaped_to
     FROM airports
    WHERE id IN (
             SELECT destination_airport_id
               FROM flights
              WHERE YEAR = 2021
                AND MONTH = 7
                AND DAY = 29
           ORDER BY HOUR,
                    MINUTE
              LIMIT 1
          );

-- The accomplice
   SELECT name AS accomplice_name
     FROM people
    WHERE phone_number IN (
             SELECT receiver
               FROM phone_calls
              WHERE YEAR = 2021
                AND MONTH = 7
                AND DAY = 28
                AND duration <= 60
                AND caller IN (
                       SELECT phone_number
                         FROM people
                        WHERE license_plate IN (
                                 SELECT license_plate
                                   FROM bakery_security_logs
                                  WHERE YEAR = 2021
                                    AND MONTH = 7
                                    AND DAY = 28
                                    AND HOUR = 10
                                    AND MINUTE >= 15
                                    AND MINUTE <= 25
                              )
                          AND id IN (
                                 SELECT person_id
                                   FROM bank_accounts
                                  WHERE account_number IN (
                                           SELECT account_number
                                             FROM atm_transactions
                                            WHERE YEAR = 2021
                                              AND MONTH = 7
                                              AND DAY = 28
                                              AND atm_location = 'Leggett Street'
                                              AND transaction_type = 'withdraw'
                                        )
                              )
                          AND passport_number IN (
                                 SELECT passport_number
                                   FROM passengers
                                  WHERE flight_id = (
                                           SELECT id
                                             FROM flights
                                            WHERE YEAR = 2021
                                              AND MONTH = 7
                                              AND DAY = 29
                                         ORDER BY HOUR,
                                                  MINUTE
                                            LIMIT 1
                                        )
                              )
                    )
          );
