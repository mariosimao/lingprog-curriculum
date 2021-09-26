CREATE TABLE student
(
    id VARCHAR(128) NOT NULL
        CONSTRAINT student_pk
            PRIMARY KEY
);

CREATE TABLE student_semester
(
    id         UUID NOT NULL
        CONSTRAINT student_semester_pk
            PRIMARY KEY,
    student_id VARCHAR(128)
        CONSTRAINT student_semester_student_id_fk
            REFERENCES student,
    name       VARCHAR(100),
    start_date DATE NOT NULL,
    end_date   DATE NOT NULL
);

CREATE TABLE subject
(
    id      UUID         NOT NULL
        CONSTRAINT subject_pk
            PRIMARY KEY,
    code    VARCHAR(7)   NOT NULL,
    name    VARCHAR(100) NOT NULL,
    credits INTEGER      NOT NULL
);

CREATE TABLE subject_corequisite
(
    subject_id     UUID
        CONSTRAINT subject_corequisite_subject_id_fk
            REFERENCES subject,
    corequisite_id UUID
        CONSTRAINT subject_corequisite_subject_id_fk_2
            REFERENCES subject
);

CREATE TABLE subject_prerequisite
(
    subject_id      UUID
        CONSTRAINT subject_prerequisite_subject_id_fk
            REFERENCES subject,
    prerequisite_id UUID
        CONSTRAINT subject_prerequisite_subject_id_fk_2
            REFERENCES subject
);

CREATE TABLE subject_attempt
(
    id          UUID NOT NULL
        CONSTRAINT subject_attempt_pk
            PRIMARY KEY,
    semester_id UUID
        CONSTRAINT subject_attempt_student_semester_id_fk
            REFERENCES student_semester,
    subject_id  UUID
        CONSTRAINT subject_attempt_subject_id_fk
            REFERENCES subject,
    professor   VARCHAR(100),
    grade       DOUBLE PRECISION
);
