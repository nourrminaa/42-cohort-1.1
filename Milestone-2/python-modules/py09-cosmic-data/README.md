_This project was developed as part of the 42 curriculum by nmina_

# Cosmic Data – Pydantic Validation

This repository contains solutions for the of the **Cosmic Data** project, introducing the core features of **Pydantic v2** through space-themed validation problems.

## Exercise 0 – Space Station Data

**Concepts learned**

- Creating models with `BaseModel`
- Using `Field()` for validation
- Default and optional fields
- Automatic `datetime` conversion
- Handling `ValidationError`

**Key features**

- String length validation
- Numeric range validation
- Default values (`is_operational`)
- Optional fields (`notes`)

---

## Exercise 1 – Alien Contact Logs

**Concepts learned**

- Enums (`Enum`)
- Custom validation with `@model_validator(mode="after")`

---

## Exercise 2 – Space Crew Management

**Concepts learned**

- Nested Pydantic models
- Lists of models
- Complex model validation

---

These exercises progressively demonstrate how Pydantic can validate simple data, enforce business rules, and manage complex nested data structures while providing clear and informative validation errors.
